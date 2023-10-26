#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Renderer/Texture.hpp"

#include <string>

#include <imgui.h>

namespace Crystal
{

	class Panels
	{
	public:
		static void Init();

		static void TexturePanel(const std::string_view& name, Ref<Texture2D>& changeAbleTexture, bool* useTexture = nullptr);

	private:
		static Ref<Texture2D> s_CheckerboardTex;
	};

}