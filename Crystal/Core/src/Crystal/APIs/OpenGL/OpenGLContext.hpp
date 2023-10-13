#pragma once

#include "Crystal/Core/Core.hpp"

#include <GLFW/glfw3.h>

#include "Crystal/Renderer/GraphicsContext.hpp"

namespace Crystal
{

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_windowHandle;
	};

}