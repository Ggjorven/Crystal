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
		explicit Panels(Ref<Project>& project);
		virtual ~Panels();

		void RunWindow(bool& running);
		void ObjectsWindow();
		void ObjectPropertiesWindow();

		void Vector3(const std::string& label, float& value, const ImVec4& colourN, const ImVec4& colourH, const ImVec4& colourP, bool renderMultiSelect);
		void TexturePanel(const std::string_view& name, Ref<Texture2D>& changeAbleTexture, bool* useTexture = nullptr);

		static void BeginColours();
		static void EndColours();

	private:
		Ref<Project>& m_Project;
		ECS::Entity* m_SelectedEntity;

		Ref<Texture2D> m_CheckerboardTex;
		Ref<Texture2D> m_ButtonTex;
	};

}