#include "crpch.h"
#include "Texture.hpp"

#include "Crystal/Renderer/Renderer.hpp"

#include "APIs/OpenGL/OpenGLTexture.hpp"
//TODO add textures

namespace Crystal
{

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::API::None not supported.");
		case RenderingAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}

		CR_CORE_ASSERT(false, "No valid API selected.");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::API::None not supported.");
		case RenderingAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}

		CR_CORE_ASSERT(false, "No valid API selected.");
		return nullptr;
	}
}