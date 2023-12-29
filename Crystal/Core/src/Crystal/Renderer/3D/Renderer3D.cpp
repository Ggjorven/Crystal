#include "crpch.h"
#include "Renderer3D.hpp"

#include "Crystal/Renderer/RendererCommand.hpp"

#include "Crystal/Renderer/VertexArray.hpp"
#include "Crystal/Renderer/Shader.hpp"

namespace Crystal
{
	struct Renderer3DStorage
	{
	public:
		Ref<VertexArray> CubeVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer3DStorage* s_CubeData;

	void Renderer3D::Init()
	{
		s_CubeData = new Renderer3DStorage();

		//Arrays
		float vertices[] = {
			// Position              // Tex coords
			-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, // Vertex 0 (Back)
			 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, // Vertex 1 (Back)
			 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, // Vertex 2 (Back)
			-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, // Vertex 3 (Back)

			-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, // Vertex 4 (Front)
			 0.5f, -0.5f,  0.5f,    1.0f, 0.0f, // Vertex 5 (Front)
			 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, // Vertex 6 (Front)
			-0.5f,  0.5f,  0.5f,    0.0f, 1.0f, // Vertex 7 (Front)

			 0.5f, -0.5f, -0.5f,    0.0f, 0.0f, // Vertex 8 (Right)
			 0.5f, -0.5f,  0.5f,    1.0f, 0.0f, // Vertex 9 (Right)
			 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, // Vertex 10 (Right)
			 0.5f,  0.5f, -0.5f,    0.0f, 1.0f, // Vertex 11 (Right)

			-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, // Vertex 12 (Left)
			-0.5f, -0.5f,  0.5f,    1.0f, 0.0f, // Vertex 13 (Left)
			-0.5f,  0.5f,  0.5f,    1.0f, 1.0f, // Vertex 14 (Left)
			-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, // Vertex 15 (Left)

			-0.5f,  0.5f, -0.5f,    0.0f, 0.0f, // Vertex 16 (Top)
			 0.5f,  0.5f, -0.5f,    1.0f, 0.0f, // Vertex 17 (Top)
			 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, // Vertex 18 (Top)
			-0.5f,  0.5f,  0.5f,    0.0f, 1.0f, // Vertex 19 (Top)

			-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, // Vertex 20 (Bottom)
			 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, // Vertex 21 (Bottom)
			 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, // Vertex 22 (Bottom)
			-0.5f, -0.5f,  0.5f,    0.0f, 1.0f  // Vertex 23 (Bottom)
		};



		uint32_t indices[] = {
			0, 1, 2, 2, 3, 0,			// Front
			4, 5, 6, 6, 7, 4,			// Back
			8, 9, 10, 10, 11, 8,		// Right
			12, 13, 14, 14, 15, 12,		// Left
			16, 17, 18, 18, 19, 16,		// Top
			20, 21, 22, 22, 23, 20		// Bottom
		};

		// Create Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
		s_CubeData->CubeVertexArray = VertexArray::Create();

		Ref<VertexBuffer> VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		VertexBuffer->SetLayout({
			BufferElement(ShaderDataType::Float3, "a_Position", false),
			BufferElement(ShaderDataType::Float2, "a_TexCoord", false)
		});

		Ref<IndexBuffer> IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		// Bind the VAO first, then bind and set VBO and IBO data
		s_CubeData->CubeVertexArray->Bind();

		s_CubeData->CubeVertexArray->AddVertexBuffer(VertexBuffer);
		s_CubeData->CubeVertexArray->AddIndexBuffer(IndexBuffer);


		//Texture & Shader
		s_CubeData->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;

		s_CubeData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));


		ShaderSource shaderSource = ShaderLib::GetShaderSource(ShaderLib::Type::Textured_Coloured_Transform_ViewProj_TexCoord);
		s_CubeData->TextureShader = Shader::Create("TexturedShader", shaderSource.VertexSource, shaderSource.FragmentSource);

		s_CubeData->TextureShader->SetUniformInt1("u_Texture", 0);
	}

	void Renderer3D::Shutdown()
	{
		delete s_CubeData;
	}

	void Renderer3D::OnDrawCall() // TODO(Jorben): Call this once when creating a renderer queue
	{
		RendererCommand::EnableDepth(true);
	}

	void Renderer3D::DrawCube(const Vec3<float>& position, const Vec3<float>& size, const Vec4<float>& colour, bool reversed, const Ref<PerspectiveCamera>& camera)
	{
		DrawCube(position, size, { 0.0f, 0.0f, 0.0f }, colour, reversed, camera);
	}

	void Renderer3D::DrawCube(const Vec3<float>& position, const Vec3<float>& size, const Vec3<float>& origin, const Vec4<float>& colour, bool reversed, const Ref<PerspectiveCamera>& camera)
	{
		//Depth
		OnDrawCall();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x + origin.x, position.y + origin.y, position.z + origin.z }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, size.z }) * glm::scale(glm::mat4(1.0f), glm::vec3((reversed ? -1.0f : 1.0f), 1.0f, 1.0f));

		s_CubeData->TextureShader->SetUniformFloat4("u_Colour", colour);

		s_CubeData->TextureShader->SetUniformFloat2("u_TexOffset", Vec2<float>(0.0f, 0.0f));
		s_CubeData->TextureShader->SetUniformFloat2("u_TexScale", Vec2<float>(1.0f, 1.0f));

		s_CubeData->TextureShader->SetUniformMat4("u_Transform", transform);
		if (camera != nullptr)
			s_CubeData->TextureShader->SetUniformMat4("u_ViewProj", camera->GetViewProjectionMatrix());
		else
			s_CubeData->TextureShader->SetUniformMat4("u_ViewProj", glm::mat4(1.0f));


		s_CubeData->WhiteTexture->Bind();
		RendererCommand::DrawIndexed(s_CubeData->CubeVertexArray, s_CubeData->TextureShader);
	}

}