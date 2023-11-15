#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/CustomTypes.hpp"

#include <glm/glm.hpp>

#include "Crystal/Renderer/Texture.hpp"
#include "Crystal/Renderer/2D/OrthoGraphicCamera.hpp"

namespace Crystal
{

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnDrawCall();

		//Rendering functions
		//
		//Coloured
		static void DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Vec4<float>& colour, bool reversed = false, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Vec2<float>& origin, const Vec4<float>& colour, bool reversed = false, const Ref<OrthoGraphicCamera>& camera = nullptr);

		//Textured
		static void DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Ref<Texture2D>& texture, bool reversed = false, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Ref<Texture2D>& texture, const TexCoords& coords, bool reversed = false, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Vec2<float>& origin, const Ref<Texture2D>& texture, bool reversed = false, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const Vec2<float>& position, const Vec2<float>& size, const Vec2<float>& origin, const Ref<Texture2D>& texture, const TexCoords& coords, bool reversed = false, const Ref<OrthoGraphicCamera>& camera = nullptr);
	
		
	};

}