#include "crpch.h"
#include "Texture.hpp"

#include "Crystal/Renderer/Renderer.hpp"

#include "APIs/OpenGL/OpenGLTexture.hpp"

namespace Crystal
{

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}
}