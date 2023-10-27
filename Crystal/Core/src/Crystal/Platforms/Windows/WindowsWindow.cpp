#include "crpch.h"
#include "WindowsWindow.hpp"

#include "Crystal/Core/Core.hpp"

#include "Crystal/Core/Events/Events.hpp"

#include "Crystal/Core/Events/Input/Input.hpp"

namespace Crystal
{

	bool WindowsWindow::s_GLFWinitialized = false;
	uint32_t WindowsWindow::s_Instances = 0;

	WindowsWindow::WindowsWindow(const WindowProperties properties)
	{
		if (!Init(properties))
		{
			CR_CORE_ASSERT(false, "Failed to create a (windows)window.");
			return;
		}
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
	}

	void WindowsWindow::OnRender()
	{
		m_Context->SwapBuffers();
	}

	bool WindowsWindow::InView(MousePosition position) const
	{
		#ifndef CR_DIST
		int padding = 5; //5 pixels //Changeable
		int topPadding = 10; //Extra 10 pixels for the top so when used in the editor and you want to pick up an imgui window it works

		#else //Turned off in dist //Also changeable in debug and release of course
		int padding = 0;
		int topPadding = 0;
		#endif

		//CR_WARN("Mouse position X: {0}, Y: {1}", position.X, position.Y);
		//CR_WARN("View position X: {0}, Y: {1}", m_Data.ViewX, m_Data.ViewY);
		//CR_WARN("View size X: {0}, Y: {1}", m_Data.ViewWidth, m_Data.ViewHeight);

		if (position.X >= m_Data.ViewX + padding && position.X <= m_Data.ViewWidth + m_Data.ViewX - padding &&
			position.Y >= m_Data.ViewY + padding + topPadding && position.Y <= m_Data.ViewHeight + m_Data.ViewY - padding)
			return false;

		return true;
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
		m_Data.Vsync = enabled;
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

		glfwSetWindowUserPointer(m_Window, &m_Data); //So we can access/get to the data in lambda functions

		//Graphics context init 
		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();
		//SetVSync(properties.VSync);

		//Event system
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				data.ViewWidth = width;
				data.ViewHeight = height;

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