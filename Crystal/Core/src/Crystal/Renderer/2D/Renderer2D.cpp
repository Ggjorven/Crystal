#include "crpch.h"
#include "Renderer2D.hpp"

#include "Crystal/Renderer/VertexArray.hpp"
#include "Crystal/Renderer/Shader.hpp"
#include "Crystal/Renderer/RendererCommand.hpp"

#include "Crystal/Core/Application.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Crystal
{
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


		// Texture & Shader
		s_QuadData->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;

		s_QuadData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));


		ShaderSource shaderSource = ShaderLib::GetShaderSource(ShaderLib::Type::Textured_Coloured_Transform_ViewProj_TexCoord);
		s_QuadData->TextureShader = Shader::Create("TexturedShader", shaderSource.VertexSource, shaderSource.FragmentSource);

		s_QuadData->TextureShader->SetUniformInt1("u_Texture", 0); // Set the texture slot to 0
	}

	void Renderer2D::Shutdown()
	{
		delete s_QuadData;
	}

	void Renderer2D::OnDrawCall()
	{
		RendererCommand::EnableDepth(false);
	}

	//Rendering
	//
	//Coloured
	void Renderer2D::DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Vec4<float>& colour, bool reversed, const Ref<OrthoGraphicCamera>& camera)
	{
		DrawQuad(position, size, { 0.0f, 0.0f }, colour, reversed, camera);
	}

	void Renderer2D::DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Vec2<float>& origin, const Vec4<float>& colour, bool reversed, const Ref<OrthoGraphicCamera>& camera)
	{
		//Depth
		OnDrawCall();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x + origin.x, position.y + origin.y, 0.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f }) * glm::scale(glm::mat4(1.0f), 
			glm::vec3((reversed ? -1.0f : 1.0f), 1.0f, 1.0f));

		s_QuadData->TextureShader->SetUniformFloat4("u_Colour", colour);

		s_QuadData->TextureShader->SetUniformFloat2("u_TexOffset", Vec2<float>(0.0f, 0.0f));
		s_QuadData->TextureShader->SetUniformFloat2("u_TexScale", Vec2<float>(1.0f, 1.0f));

		s_QuadData->TextureShader->SetUniformMat4("u_Transform", transform);
		if (camera != nullptr) 
			s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", camera->GetViewProjectionMatrix());
		else 
			s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", glm::mat4(1.0f));


		s_QuadData->WhiteTexture->Bind(0); // Bind the white texture to texture slot 0 since that's where it's specified in the shader uniform
		RendererCommand::DrawIndexed(s_QuadData->QuadVertexArray, s_QuadData->TextureShader);
	}

	//Textured
	void Renderer2D::DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Ref<Texture2D>& texture, bool reversed, const Ref<OrthoGraphicCamera>& camera)
	{
		DrawQuad(position, size, { 0.0f, 0.0f }, texture, TexCoords(0u, 0u, texture->GetWidth(), texture->GetHeight()), reversed, camera);
	}

	void Renderer2D::DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Ref<Texture2D>& texture, const TexCoords& coords, bool reversed, const Ref<OrthoGraphicCamera>& camera)
	{
		DrawQuad(position, size, { 0.0f, 0.0f }, texture, coords, reversed, camera);
	}

	void Renderer2D::DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Vec2<float>& origin, const Ref<Texture2D>& texture, bool reversed, const Ref<OrthoGraphicCamera>& camera)
	{
		DrawQuad(position, size, origin, texture, TexCoords(0u, 0u, texture->GetWidth(), texture->GetHeight()), reversed, camera);
	}

	void Renderer2D::DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Vec2<float>& origin, const Ref<Texture2D>& texture, const TexCoords& coords, bool reversed, const Ref<OrthoGraphicCamera>& camera)
	{
		//Depth
		OnDrawCall();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x + origin.x, position.y + origin.y, 0.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3((reversed ? -1.0f : 1.0f), 1.0f, 1.0f));

		s_QuadData->TextureShader->SetUniformFloat4("u_Colour", Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f));

		uint32_t textureWidth = texture->GetWidth();
		uint32_t textureHeight = texture->GetHeight();

		s_QuadData->TextureShader->SetUniformFloat2("u_TexOffset", { (float)coords.X / (float)textureWidth, ( (float)textureHeight - (float)coords.Y - coords.Height) / (float)textureHeight });
		s_QuadData->TextureShader->SetUniformFloat2("u_TexScale", { (float)coords.Width / (float)textureWidth, (float)coords.Height / (float)textureHeight });
		
		s_QuadData->TextureShader->SetUniformMat4("u_Transform", transform);
		if (camera != nullptr)
			s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", camera->GetViewProjectionMatrix());
		else
			s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", glm::mat4(1.0f));


		texture->Bind(0); // Bind the white texture to texture slot 0 since that's where it's specified in the shader uniform
		RendererCommand::DrawIndexed(s_QuadData->QuadVertexArray, s_QuadData->TextureShader);
	}

}