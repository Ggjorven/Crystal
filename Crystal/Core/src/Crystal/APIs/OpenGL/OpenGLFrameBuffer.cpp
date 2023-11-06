#include "crpch.h"
#include "OpenGLFrameBuffer.hpp"

#include <GL/glew.h>

namespace Crystal
{

	OpenGLFrameBuffer::OpenGLFrameBuffer(uint32_t width, uint32_t height, FrameBufferFormat format)
		: m_Format(format)
	{
		Resize(width, height);
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (m_Width == width && m_Height == height)
			return;

		m_Width = width;
		m_Height = height;

		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}

		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glGenTextures(1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);

		if (m_Format == FrameBufferFormat::RGBA16F)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
		else if (m_Format == FrameBufferFormat::RGBA8)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		glGenTextures(1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Width, m_Height, 0,
			GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
		);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			CR_CORE_ASSERT(false, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, m_Width, m_Height);

		//Texture creation
		m_Texture = Texture2D::Create(m_Width, m_Height);

		FBData data = GetFramebufferData();
		m_Texture->SetData(data.Data, data.Size);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void OpenGLFrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::BindTexture(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
	}

	OpenGLFrameBuffer::FBData OpenGLFrameBuffer::GetFramebufferData()
	{
		// Note(Jorben): This function is currently in beta and only supports RGBA as a framebuffer format.
		// Allocate memory for the data (make sure to free it when done)
		void* data = malloc(m_Width * m_Height * 4); // * 4 for RGBA format

		Bind();
		glReadPixels(0, 0, m_Width, m_Height, (m_Format == FrameBufferFormat::RGBA8 ? GL_RGBA : GL_RGBA16F), GL_UNSIGNED_BYTE, data);
		Unbind();

		return FBData(data, m_Width * m_Height * 4);
	}

}