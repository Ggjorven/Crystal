#include "crpch.h"
#include "VertexArray.hpp"

#include "Crystal/Renderer/Renderer.hpp"
#include "APIs/OpenGL/OpenGLVertexArray.hpp"
//TODO add vertex arrays

namespace Crystal
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RendereringAPI none not supported."); break;
		case RenderingAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		CR_CORE_ASSERT(false, "No proper RenderingAPI selected.");
		return nullptr;
	}

}