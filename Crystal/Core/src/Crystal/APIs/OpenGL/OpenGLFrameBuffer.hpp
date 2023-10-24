#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Renderer/FrameBuffer.hpp"

namespace Crystal
{

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(uint32_t width, uint32_t height, FrameBufferFormat format);
		virtual ~OpenGLFrameBuffer();

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void BindTexture(uint32_t slot = 0) const override;

		virtual uint32_t GetRendererID() const { return m_RendererID; }
		virtual uint32_t GetColorAttachmentRendererID() const { return m_ColorAttachment; }
		virtual uint32_t GetDepthAttachmentRendererID() const { return m_DepthAttachment; }

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual FrameBufferFormat GetFormat() const override { return m_Format; }

		virtual Ref<Texture2D>& GetTexture() override { return m_Texture; }

	private:
		struct FBData
		{
		public:
			void* Data;
			uint32_t Size;

			FBData(void* data, uint32_t size)
				: Data(data), Size(size)
			{
			}

			virtual ~FBData()
			{
				free(Data);
			}
		};

		FBData GetFramebufferData();

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_Width, m_Height;
		FrameBufferFormat m_Format;

		uint32_t m_ColorAttachment, m_DepthAttachment;

		Ref<Texture2D> m_Texture;
	};

}