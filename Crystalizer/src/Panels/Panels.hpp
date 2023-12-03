#pragma once

#include <Crystal/Core/Core.hpp>
#include <Crystal/Utils/CustomTypes.hpp>
#include <Crystal/Renderer/Texture.hpp>
#include <Crystal/Data/Project/Project.hpp>

#include <utility>
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
		void ProjectSettingsWindow(bool* projOpen);
		void SceneSettingsWindow(bool* sceneOpen);

		void TexturePanel(const std::string_view& name, Ref<Texture2D>& changeAbleTexture, bool* useTexture = nullptr);
		
		static void SwitchButtons();

		static void BeginColours();
		static void EndColours();

	public:
		static Ref<Texture2D> s_ButtonTex;

	private:
		enum class ButtonState
		{
			None = 0, Play, Pause
		};
		
		enum class Icon
		{
			None = -1, Tag = 0, Transform, Renderer2D, Script
		};

		static ButtonState s_ButtonState;
		static std::array<Ref<Texture2D>, 2> s_Buttons;
		static std::array<Ref<Texture2D>, 4> s_Icons;
		
		Ref<Project>& m_Project;
		Ref<ECS::Entity> m_SelectedEntity;

		Ref<Texture2D> m_CheckerboardTex;

		bool m_StartUp = true;
	};

}