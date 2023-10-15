#pragma once

#include "Crystal/Core/Core.hpp"

#include <glm/glm.hpp>

#include "Crystal/Renderer/Texture.hpp"

#include "Crystal/Renderer/OrthoGraphicCamera.hpp"

namespace Crystal
{

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		//Rendering functions
		//
		//Coloured
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec2& origin, const glm::vec4& colour, const Ref<OrthoGraphicCamera>& camera = nullptr);

		//Textured
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const TexCoords& coords, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec2& origin, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec2& origin, const Ref<Texture2D>& texture, const TexCoords& coords, const Ref<OrthoGraphicCamera>& camera = nullptr);
	};

}