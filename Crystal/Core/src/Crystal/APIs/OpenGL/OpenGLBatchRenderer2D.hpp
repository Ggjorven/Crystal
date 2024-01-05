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
		std::vector<BatchRenderer2D::QuadVertexData> m_Vertices;
		std::vector<unsigned int> m_Indices;
		unsigned int m_VAO, m_VBO, m_IBO;

		unsigned int m_MaxQuads = 1000u;
		unsigned int m_QuadCount = 0u;

		Ref<OpenGLShader> m_Shader = nullptr;
	};

}