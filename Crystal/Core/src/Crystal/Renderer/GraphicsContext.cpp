#include "crpch.h"
#include "GraphicsContext.hpp"

#include <GLFW/glfw3.h>

#include "Crystal/Renderer/Renderer.hpp"

#include "Crystal/APIs/OpenGL/OpenGLContext.hpp"

namespace Crystal
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_CRITICAL("Rendering API: None is not allowed {0} {1}", __FILE__, __LINE__);
		case RenderingAPI::API::OpenGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		return nullptr;
	}
}