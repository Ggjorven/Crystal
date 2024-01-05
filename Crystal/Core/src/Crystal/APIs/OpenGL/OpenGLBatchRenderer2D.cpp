#include "crpch.h"
#include "OpenGLBatchRenderer2D.hpp"

#include "Crystal/Renderer/RendererCommand.hpp"

namespace Crystal
{

	void OpenGLBatchRenderer2D::InitImplementation()
	{
		m_Vertices.reserve(m_MaxQuads * 4);
		m_Indices.reserve(m_MaxQuads * 6);

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		m_VBO = CreateRef<OpenGLVertexBuffer>(nullptr, sizeof(BatchRenderer2D::QuadVertexData) * m_MaxQuads * 4, OpenGLBufferUsage::DYNAMIC_DRAW);

		for (unsigned int i = 0, offset = 0; i < m_MaxQuads * 6; i += 6, offset += 4)
		{
			m_Indices.push_back(offset + 0);
			m_Indices.push_back(offset + 1);
			m_Indices.push_back(offset + 2);

			m_Indices.push_back(offset + 2);
			m_Indices.push_back(offset + 3);
			m_Indices.push_back(offset + 0);
		}

		m_IBO = CreateRef<OpenGLIndexBuffer>(m_Indices.data(), m_Indices.size(), OpenGLBufferUsage::STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(BatchRenderer2D::QuadVertexData), (void*)offsetof(BatchRenderer2D::QuadVertexData, Position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BatchRenderer2D::QuadVertexData), (void*)offsetof(BatchRenderer2D::QuadVertexData, Colour));

		m_VBO->UnBind();
		glBindVertexArray(0);

		// TODO(Jorben): Rewrite the shader
		ShaderSource src = ShaderLib::GetShaderSource(ShaderLib::Type::Batch_Quad);
		m_Shader = CreateRef<OpenGLShader>("Batch", src.VertexSource, src.FragmentSource);
	}

	void OpenGLBatchRenderer2D::ShutdownImplementation()
	{
		glDeleteVertexArrays(1, &m_VAO);
	}

	void OpenGLBatchRenderer2D::BeginBatchImplementation()
	{
		m_QuadCount = 0u;
		m_Vertices.clear();
	}

	void OpenGLBatchRenderer2D::EndBatchImplementation()
	{
		m_VBO->Bind();
		m_VBO->SetSubData(0, (void*)m_Vertices.data(), m_Vertices.size() * sizeof(BatchRenderer2D::QuadVertexData));
		m_VBO->UnBind();
	}

	void OpenGLBatchRenderer2D::FlushBatchImplementation()
	{
		m_Shader->Bind();
		glBindVertexArray(m_VAO);
		m_IBO->Bind();
		glDrawElements(GL_TRIANGLES, m_QuadCount * 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		m_Shader->UnBind();
	}

	void OpenGLBatchRenderer2D::AddQuadImplementation(const BatchRenderer2D::Quad& quad)
	{
		if (m_QuadCount >= m_MaxQuads)
		{
			EndBatchImplementation();
			FlushBatchImplementation();
			BeginBatchImplementation();
		}

		glm::vec2 p0 = quad.Position;
		glm::vec2 p1 = glm::vec2(quad.Position.x + quad.Size.x, quad.Position.y);
		glm::vec2 p2 = glm::vec2(quad.Position.x + quad.Size.x, quad.Position.y + quad.Size.y);
		glm::vec2 p3 = glm::vec2(quad.Position.x, quad.Position.y + quad.Size.y);

		m_Vertices.push_back({ p0, quad.Colour });
		m_Vertices.push_back({ p1, quad.Colour });
		m_Vertices.push_back({ p2, quad.Colour });
		m_Vertices.push_back({ p3, quad.Colour });

		m_QuadCount++;
	}
}