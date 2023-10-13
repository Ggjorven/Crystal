#include "crpch.h"
#include "RenderingAPI.hpp"

#include "APIs/OpenGL/OpenGLRenderingAPI.hpp"
//#include "APIs/Vulkan/VulkanRendererAPI.hpp"

namespace Crystal
{
																	//
	RenderingAPI::API RenderingAPI::s_API = RenderingAPI::API::OpenGL; //Select RendererAPI here
																	//
	Scope<RenderingAPI> RenderingAPI::Create()
	{
		switch (s_API)
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL: return CreateScope<OpenGLRenderingAPI>();
		//case RenderingAPI::API::Vulkan: return CreateScope<VulkanRenderingAPI>();
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}
}