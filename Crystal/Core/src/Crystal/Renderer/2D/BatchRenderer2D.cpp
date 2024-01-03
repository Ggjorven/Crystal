#include "crpch.h"
#include "BatchRenderer2D.hpp"

#include "Crystal/Renderer/Renderer.hpp"

#include "Crystal/APIs/OpenGL/OpenGLBatchRenderer2D.hpp"

namespace Crystal
{

	BatchRenderer2D* BatchRenderer2D::s_Instance = nullptr;

	void BatchRenderer2D::Init()
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::OpenGL: 
			s_Instance = new OpenGLBatchRenderer2D(); 
			break;

		case RenderingAPI::API::Vulkan:
			CR_CORE_ASSERT(false, "Vulkan BatchRenderer2D is not supported yet!");
			break;

		default:
			CR_CORE_ASSERT(false, "Unknown Rendering API!");
			break;
		}

		s_Instance->InitImplementation();
	}

}