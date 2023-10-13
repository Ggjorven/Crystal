#include "crpch.h"
#include "OpenGLContext.hpp"


#include <GL/glew.h>
#include <GL/GL.h>


namespace Crystal
{

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_windowHandle(window)
	{
		//EX_WARN("OpenGL Constructor.");
		if (window == nullptr) CR_CRITICAL("Window handle passed in is a nullptr! {0} {1}", __FILE__, __LINE__);
	}

	void OpenGLContext::Init()
	{
		//EX_WARN("OpenGL Init.");
		glfwMakeContextCurrent(m_windowHandle);
		
		int status = glewInit();
		if (status != GLEW_OK) CR_CORE_CRITICAL("Failed to initialize glew!");

		CR_CORE_INFO("OpenGL Info:");
		CR_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		CR_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		CR_CORE_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		
	}

	void OpenGLContext::SwapBuffers()
	{
		//CR_WARN("OpenGL SwapBuffers.");
		glfwSwapBuffers(m_windowHandle);
	}

}