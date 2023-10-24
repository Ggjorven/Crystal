#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Renderer/Texture.hpp"

namespace Crystal
{

	enum class FrameBufferFormat
	{
		None = 0,
		RGBA8 = 1,
		RGBA16F = 2
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual void BindTexture(uint32_t slot = 0) const = 0;

		virtual uint32_t GetRendererID() const = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;
		virtual uint32_t GetDepthAttachmentRendererID() const = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual FrameBufferFormat GetFormat() const = 0;

		virtual Ref<Texture2D>& GetTexture() = 0;

	public:
		static Ref<FrameBuffer> Create(uint32_t width, uint32_t height, FrameBufferFormat format);
	};

}