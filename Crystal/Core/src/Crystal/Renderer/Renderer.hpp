#pragma once

#include "Crystal/Core/Core.hpp"

#include <glm/glm.hpp>

#include "RenderingAPI.hpp"

namespace Crystal
{

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		//static void BeginScene(OrthographicCamera& camera);
		//static void EndScene();

		//static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }

	private:
		/*
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
		*/
	};

}