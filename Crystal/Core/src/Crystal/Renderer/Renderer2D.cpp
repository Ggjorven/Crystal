#include "crpch.h"
#include "Renderer2D.hpp"

#include "Crystal/Renderer/VertexArray.hpp"
#include "Crystal/Renderer/Shader.hpp"
#include "Crystal/Renderer/RendererCommand.hpp"

#include "Crystal/Core/Application.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Crystal
{
	glm::vec2 Renderer2D::s_Origin = glm::vec2(0.0f, 0.0f);

	struct Renderer2DStorage
	{
	public:
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_QuadData;


	void Renderer2D::Init()
	{
		s_QuadData = new Renderer2DStorage();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		// Create Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
		s_QuadData->QuadVertexArray = Crystal::VertexArray::Create();

		Crystal::Ref<Crystal::VertexBuffer> VertexBuffer = Crystal::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		VertexBuffer->SetLayout({ 
			Crystal::BufferElement(Crystal::ShaderDataType::Float3, "a_Position", false),
			Crystal::BufferElement(Crystal::ShaderDataType::Float2, "a_TexCoord", false)
			});

		Crystal::Ref<Crystal::IndexBuffer> IndexBuffer = Crystal::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		// Bind the VAO first, then bind and set VBO and IBO data
		s_QuadData->QuadVertexArray->Bind();

		s_QuadData->QuadVertexArray->AddVertexBuffer(VertexBuffer);
		s_QuadData->QuadVertexArray->AddIndexBuffer(IndexBuffer);


		//Texture & Shader
		s_QuadData->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;

		s_QuadData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));


		ShaderSource shaderSource = ShaderLib::GetShaderSource(ShaderLib::Type::Textured_Coloured_Transform_ViewProj);
		s_QuadData->TextureShader = Shader::Create("TexturedShader", shaderSource.VertexSource, shaderSource.FragmentSource);

		s_QuadData->TextureShader->SetUniformInt1("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_QuadData;
	}

	//================
	//Coloured Quads
	//================
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, camera, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x - s_Origin.x, position.y - s_Origin.y, position.z  })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_QuadData->TextureShader->SetUniformMat4("u_Transform", transform);

		if (camera != nullptr) s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", camera->GetViewProjectionMatrix());
		else s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", glm::mat4(1.0f));

		s_QuadData->TextureShader->SetUniformFloat4("u_Colour", color);


		s_QuadData->WhiteTexture->Bind();
		RendererCommand::DrawIndexed(s_QuadData->QuadVertexArray, s_QuadData->TextureShader);
	}

	//+ rotation
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, camera, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x - s_Origin.x, position.y - s_Origin.y, position.z })
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_QuadData->TextureShader->SetUniformMat4("u_Transform", transform);

		if (camera != nullptr) s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", camera->GetViewProjectionMatrix());
		else s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", glm::mat4(1.0f));

		s_QuadData->TextureShader->SetUniformFloat4("u_Colour", color);


		s_QuadData->WhiteTexture->Bind();
		RendererCommand::DrawIndexed(s_QuadData->QuadVertexArray, s_QuadData->TextureShader);
	}

	//================
	//Textured quads
	//================
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, camera);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x - s_Origin.x, position.y - s_Origin.y, position.z })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_QuadData->TextureShader->SetUniformMat4("u_Transform", transform);

		if (camera != nullptr) s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", camera->GetViewProjectionMatrix());
		else s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", glm::mat4(1.0f));

		s_QuadData->TextureShader->SetUniformFloat4("u_Colour", glm::vec4(1.0f));


		texture->Bind();
		RendererCommand::DrawIndexed(s_QuadData->QuadVertexArray, s_QuadData->TextureShader);
	}

	//+ rotation
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture, camera, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x - s_Origin.x, position.y - s_Origin.y, position.z})
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f});

		s_QuadData->TextureShader->SetUniformMat4("u_Transform", transform);

		if (camera != nullptr) s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", camera->GetViewProjectionMatrix());
		else s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", glm::mat4(1.0f));

		s_QuadData->TextureShader->SetUniformFloat4("u_Colour", color);


		texture->Bind();
		RendererCommand::DrawIndexed(s_QuadData->QuadVertexArray, s_QuadData->TextureShader);
	}

}