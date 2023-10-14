#pragma once

#include "Crystal/Core/Core.hpp"

#include <glm/glm.hpp>

#include "Crystal/Renderer/Texture.hpp"

#include "Crystal/Renderer/OrthoGraphicCamera.hpp"

namespace Crystal
{
	/*
		Everything in this class is related to the camera specifications
		such as the position, size, origin.
	*/
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		//static void BeginScene(const OrthographicCamera& camera); //TODO
		//static void EndScene();

		static void SetQuadOrigin(glm::vec2 origin) { s_Origin = origin; }
		static glm::vec2 GetQuadOrigin() { return s_Origin; }
		// Drawing functions
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	private:
		static glm::vec2 s_Origin;
	};

}