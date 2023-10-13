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
		case RenderingAPI::API::None: CR_CORE_CRITICAL("No RendererAPI selected... {0} : {1}", __FILE__, __LINE__);
		case RenderingAPI::API::OpenGL: return CreateScope<OpenGLRenderingAPI>();
		//case RenderingAPI::API::Vulkan: return CreateScope<VulkanRenderingAPI>();
		}

		return nullptr;
	}
}