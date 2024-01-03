#include "crpch.h"
#include "OpenGLBatchRenderer2D.hpp"

#include "Crystal/Renderer/RendererCommand.hpp"

namespace Crystal
{

	void OpenGLBatchRenderer2D::InitImplementation()
	{
		std::vector<uint32_t> indices = { };
		// Note(Jorben): * 6 for the 6 incices per quad
		indices.reserve(m_MaxQuads * 6);
		for (uint32_t i = 0; i < m_MaxQuads; i++)
		{
			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 0);
		}

		// Note(Jorben): * 4 for the 4 vertices per quad
		m_Vertices.reserve(m_MaxQuads * 4);
		
		m_VAO = CreateRef<OpenGLVertexArray>();
		m_VAO->Bind();

		// TODO(Jorben): Set the actual layout
		m_VBO = CreateRef<OpenGLVertexBuffer>(nullptr, (uint32_t)sizeof(BatchRenderer2D::QuadVertexData) * m_MaxQuads, OpenGLBufferUsage::DYNAMIC_DRAW);
		m_VBO->SetLayout({
			Crystal::BufferElement(Crystal::ShaderDataType::Float2, "a_Position", false),
			//Crystal::BufferElement(Crystal::ShaderDataType::Float2, "a_TexCoord", false),
			//Crystal::BufferElement(Crystal::ShaderDataType::Float2, "a_Size", false),
			Crystal::BufferElement(Crystal::ShaderDataType::Float4, "a_Colour", false)
		});
		
		// Note(Jorben): * 6 for the 6 indices per quad
		m_IBO = CreateRef<OpenGLIndexBuffer>(indices.data(), m_MaxQuads * 6, OpenGLBufferUsage::STATIC_DRAW);

		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->AddIndexBuffer(m_IBO);

		//m_VBO->UnBind(); // It gets bound in the constructor
		m_VAO->UnBind();

		// Create Shader // TODO(Jorben): Rewrite the shader
		m_Shader = CreateRef<OpenGLShader>("Batch", ShaderLib::GetShaderSource(ShaderLib::Type::Batch_Quad).VertexSource, ShaderLib::GetShaderSource(ShaderLib::Type::Batch_Quad).FragmentSource);
	}

	void OpenGLBatchRenderer2D::ShutdownImplementation()
	{
	}

	void OpenGLBatchRenderer2D::BeginBatchImplementation()
	{
		//m_QuadQueue.clear();
		//m_QuadVertices.clear();
		//m_Vertices.clear();
	}

	void OpenGLBatchRenderer2D::EndBatchImplementation()
	{
		m_VBO->Bind();
		m_VBO->SetSubData(0, m_Vertices.data(), (int)m_QuadQueue.size() * sizeof(float) * 6 * 4);
		m_VBO->UnBind();
	}

	void OpenGLBatchRenderer2D::FlushBatchImplementation()
	{
		//CR_CORE_TRACE("Pos: {0} {1}", m_QuadQueue[0].Position.x, m_QuadQueue[0].Position.y);
		//CR_CORE_TRACE("Size: {0} {1}", m_QuadQueue[0].Size.x, m_QuadQueue[0].Size.y);
		//CR_CORE_TRACE("Colour: {0} {1} {2} {3}", m_QuadQueue[0].Colour.r, m_QuadQueue[0].Colour.g, m_QuadQueue[0].Colour.b, m_QuadQueue[0].Colour.a);

		m_Shader->Bind();
		m_VAO->Bind();
		//glDrawArrays(GL_TRIANGLES, 0, (int)m_QuadQueue.size() * 6);
		glDrawElements(GL_TRIANGLES, (int)m_QuadQueue.size() * 6, GL_UNSIGNED_INT, nullptr);
		m_VAO->UnBind();
		m_Shader->UnBind();

		//CR_CORE_TRACE("______________");
		//for (auto& i : m_Vertices)
		//{
		//	CR_CORE_TRACE("{0}", i);
		//}
		//CR_CORE_TRACE("______________");
	}

	void OpenGLBatchRenderer2D::AddQuadImplementation(const BatchRenderer2D::Quad& quad)
	{
		glm::vec2 p0 = quad.Position;
		glm::vec2 p1 = glm::vec2(quad.Position.x + quad.Size.x, quad.Position.y);
		glm::vec2 p2 = glm::vec2(quad.Position.x + quad.Size.x, quad.Position.y + quad.Size.y);
		glm::vec2 p3 = glm::vec2(quad.Position.x, quad.Position.y + quad.Size.y);

		// First triangle
		m_QuadVertices.push_back({ p0, glm::vec4(quad.Colour) });
		m_QuadVertices.push_back({ p1, glm::vec4(quad.Colour) });
		m_QuadVertices.push_back({ p2, glm::vec4(quad.Colour) });

		// Second triangle
		m_QuadVertices.push_back({ p0, glm::vec4(quad.Colour) });
		m_QuadVertices.push_back({ p2, glm::vec4(quad.Colour) });
		m_QuadVertices.push_back({ p3, glm::vec4(quad.Colour) });

		m_Vertices.push_back(p0.x);
		m_Vertices.push_back(p0.y);
		m_Vertices.push_back(quad.Colour.r);
		m_Vertices.push_back(quad.Colour.g);
		m_Vertices.push_back(quad.Colour.b);
		m_Vertices.push_back(quad.Colour.a);

		m_Vertices.push_back(p1.x);
		m_Vertices.push_back(p1.y);
		m_Vertices.push_back(quad.Colour.r);
		m_Vertices.push_back(quad.Colour.g);
		m_Vertices.push_back(quad.Colour.b);
		m_Vertices.push_back(quad.Colour.a);

		m_Vertices.push_back(p2.x);
		m_Vertices.push_back(p2.y);
		m_Vertices.push_back(quad.Colour.r);
		m_Vertices.push_back(quad.Colour.g);
		m_Vertices.push_back(quad.Colour.b);
		m_Vertices.push_back(quad.Colour.a);

		m_Vertices.push_back(p3.x);
		m_Vertices.push_back(p3.y);
		m_Vertices.push_back(quad.Colour.r);
		m_Vertices.push_back(quad.Colour.g);
		m_Vertices.push_back(quad.Colour.b);
		m_Vertices.push_back(quad.Colour.a);

		// remove
		m_QuadQueue.push_back(quad);
	}
}