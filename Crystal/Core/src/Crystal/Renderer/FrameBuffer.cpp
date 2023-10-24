#include "crpch.h"
#include "FrameBuffer.hpp"

#include "Crystal/Renderer/Renderer.hpp"

#include "Crystal/APIs/OpenGL/OpenGLFrameBuffer.hpp"

namespace Crystal
{

	Ref<FrameBuffer> FrameBuffer::Create(uint32_t width, uint32_t height, FrameBufferFormat format)
	{
		Ref<FrameBuffer> buffer = nullptr;

		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::None:		return buffer;
		case RenderingAPI::API::OpenGL:		buffer = CreateScope<OpenGLFrameBuffer>(width, height, format);
		}

		return buffer;
	}

}