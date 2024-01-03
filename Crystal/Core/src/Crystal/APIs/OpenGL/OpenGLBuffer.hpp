#pragma once

#include "Crystal/Renderer/Buffer.hpp"

#include <GL/glew.h>

namespace Crystal
{

	enum class OpenGLBufferUsage
	{
		None = 0,

		STREAM_DRAW = GL_STREAM_DRAW,
		STREAM_READ = GL_STREAM_READ,
		STREAM_COPY = GL_STREAM_COPY,
		STATIC_DRAW = GL_STATIC_DRAW,
		STATIC_READ = GL_STATIC_READ,
		STATIC_COPY = GL_STATIC_COPY,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW, 
		DYNAMIC_READ = GL_DYNAMIC_READ, 
		DYNAMIC_COPY = GL_DYNAMIC_COPY
	};

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size, OpenGLBufferUsage usage);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void UnBind() const override;

		void SetSubData(uint32_t offset, float* data, uint32_t size);

		const BufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};



	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count, OpenGLBufferUsage usage);
		virtual ~OpenGLIndexBuffer();

		void Bind() const;
		void Unbind() const;

		uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}