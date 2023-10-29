#pragma once

#include <Crystal/Core/Core.hpp>
#include <Crystal/Renderer/Texture.hpp>
#include <Crystal/Data/Project/Project.hpp>

#include <string>

#include <imgui.h>

namespace Crystal
{

	class Panels
	{
	public:
		Panels(Ref<Project>& project);
		virtual ~Panels();

		void ObjectsWindow();
		void ObjectPropertiesWindow();
		void TexturePanel(const std::string_view& name, Ref<Texture2D>& changeAbleTexture, bool* useTexture = nullptr);

		static void BeginColours();
		static void EndColours();

	private:
		Ref<Project>& m_Project;

		ECS::Entity* m_SelectedEntity;

		Ref<Texture2D> m_CheckerboardTex;

	};

}