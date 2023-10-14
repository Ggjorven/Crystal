#include "crpch.h"
#include "OpenGLContext.hpp"


#include <GL/glew.h>
#include <GL/GL.h>


namespace Crystal
{

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_windowHandle(window)
	{
		if (window == nullptr) CR_CORE_ASSERT(false, "Window handle passed in is NULL!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		
		if (glewInit() != GLEW_OK) CR_CORE_ASSERT(false, "Failed to initialize glew!");

		CR_CORE_INFO("OpenGL Info:");
		CR_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		CR_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		CR_CORE_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}