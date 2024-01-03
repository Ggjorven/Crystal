#pragma once

#include "Crystal/Renderer/2D/BatchRenderer2D.hpp"

#include "Crystal/APIs/OpenGL/OpenGLShader.hpp"

#include "Crystal/APIs/OpenGL/OpenGLBuffer.hpp"
#include "Crystal/APIs/OpenGL/OpenGLVertexArray.hpp"

namespace Crystal
{

	class OpenGLBatchRenderer2D : public BatchRenderer2D
	{
	private:
		virtual void InitImplementation() override;
		virtual void ShutdownImplementation() override;

		virtual void BeginBatchImplementation() override;
		virtual void EndBatchImplementation() override;

		virtual void FlushBatchImplementation() override;

		virtual void AddQuadImplementation(const BatchRenderer2D::Quad& quad) override;

	private:
		Ref<OpenGLVertexBuffer> m_VBO = nullptr;
		Ref<OpenGLIndexBuffer> m_IBO = nullptr;
		Ref<OpenGLVertexArray> m_VAO = nullptr;

		Ref<OpenGLShader> m_Shader = nullptr;

		std::vector<BatchRenderer2D::Quad> m_QuadQueue = { }; // TODO(Jorben): Remove?
		std::vector<BatchRenderer2D::QuadVertexData> m_QuadVertices = { };
		std::vector<float> m_Vertices = { };
		//std::vector<BatchRenderer2D::Quad> m_QuadQueue = { };
		//uint32_t m_QuadCount = 0u;
	};

}