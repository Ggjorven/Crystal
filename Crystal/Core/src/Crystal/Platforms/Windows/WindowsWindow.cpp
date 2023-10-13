#include "crpch.h"
#include "WindowsWindow.hpp"

#include "Crystal/Core/Core.hpp"

#include "Crystal/Events/Event.hpp"
#include "Crystal/Events/ApplicationEvent.hpp"
#include "Crystal/Events/KeyEvent.hpp"
#include "Crystal/Events/MouseEvent.hpp"

namespace Crystal
{

	bool WindowsWindow::s_GLFWinitialized = false;
	uint32_t WindowsWindow::s_Instances = 0;

	WindowsWindow::WindowsWindow(const WindowProperties properties)
	{
		if (!Init(properties))
		{
			CR_CORE_CRITICAL("Failed to create a (windows)window.");
			return;
		}
		//EX_CORE_INFO("WindowsWindow created!");
	}

	WindowsWindow::~WindowsWindow()
	{
		//EX_CORE_INFO("WindowsWindow destroyed...");
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
	}

	void WindowsWindow::OnRender()
	{
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
		m_Data.Vsync = enabled;
		//EX_INFO("VSync: {0}", enabled);
	}


	bool WindowsWindow::Init(WindowProperties properties)
	{
		//Setup
		int succes = glfwInit();
		if (!succes)
		{
			CR_CORE_CRITICAL("Failed to initialize GLFW.");
			return 0;
		}
		s_GLFWinitialized = true;
		glfwSetErrorCallback(ErrorCallBack);

		//Window creation
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, properties.Name.c_str(), nullptr, nullptr);
		s_Instances++;

		glfwSetWindowUserPointer(m_Window, &m_Data); //So we can access the data

		//Graphics context init 
		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();
		//SetVSync(true);

		//Event system
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.CallBack(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.CallBack(event);
			});

		
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.CallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.CallBack(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.CallBack(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.CallBack(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.CallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.CallBack(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.CallBack(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.CallBack(event);
			});
		

		return 1;
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		s_Instances--;

		if (s_Instances == 0)
			glfwTerminate();
	}

	void WindowsWindow::ErrorCallBack(int errorCode, const char* description)
	{
		CR_CORE_ERROR("GLFW error ({0}) ... {1}", errorCode, description);
	}

}