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
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}
}