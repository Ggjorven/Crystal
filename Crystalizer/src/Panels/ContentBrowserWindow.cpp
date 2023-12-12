#include "Panels.hpp"

namespace Crystal
{

	void Panels::ContentBrowserWindow()
	{
		Panels::BeginColours();
		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		ImGui::Begin("Content Browser", (bool*)0, flags);

		for (auto& scene : m_Project->GetScenes())
		{
			ImVec2 cursorPos = ImGui::GetCursorPos();
			if (ImGui::Button((scene.Name + std::string("##") + scene.Path.string()).c_str(), ImVec2(64.f, 64.f)))
			{
				m_Project->SaveScene();
				m_StartUp = true;

				m_Project->SetScene(scene);
				CR_CORE_TRACE("--Scene--");
				CR_CORE_TRACE("Name: {0}", scene.Name);
				CR_CORE_TRACE("Path: {0}", scene.Path.string());
				CR_CORE_TRACE("Type: {0}", (int)scene.SceneType);
			}
			ImGui::SameLine();
		}

		if (ImGui::Button("Add New Scene"))
		{
			//m_Project->SetScene()
		}

		Panels::EndColours();
		ImGui::End();
	}

}