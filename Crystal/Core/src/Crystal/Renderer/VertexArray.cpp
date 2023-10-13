#include "crpch.h"
#include "VertexArray.hpp"

#include "Crystal/Renderer/Renderer.hpp"
#include "APIs/OpenGL/OpenGLVertexArray.hpp"

namespace Crystal
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}

}