#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Renderer/ComputeShader.hpp"
#include "Crystal/APIs/OpenGL/OpenGLComputeShader.hpp"

#include "Crystal/Renderer/Renderer.hpp"

namespace Crystal
{

	template<typename TInput, typename TOutput>
	static Ref<ComputeShader<TInput, TOutput>> CreateComputeShader(std::filesystem::path path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL: return CreateRef<OpenGLComputeShader<TInput, TOutput>>(path);
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}

	template<typename TInput, typename TOutput>
	static Ref<ComputeShader<TInput, TOutput>> CreateComputeShader(const std::string& source)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None: CR_CORE_ASSERT(false, "RenderingAPI::None is currently not supported!"); return nullptr;
		case RenderingAPI::API::OpenGL: return CreateRef<OpenGLComputeShader<TInput, TOutput>>(source);
		}

		CR_CORE_ASSERT(false, "Unknown RenderingAPI!");
		return nullptr;
	}

}