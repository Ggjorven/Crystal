#include "Panels.hpp"

#include <fstream>

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
				//CR_CORE_TRACE("--Scene--");
				//CR_CORE_TRACE("Name: {0}", scene.Name);
				//CR_CORE_TRACE("Path: {0}", scene.Path.string());
				//CR_CORE_TRACE("Type: {0}", (int)scene.SceneType);
			}
			ImGui::SameLine();
		}

		if (ImGui::Button("Add New Scene", ImVec2(128.f, 32.f)))
		{
			// Create scene
			auto path = m_Project->GetProjectDir() / m_Project->GetSceneDir() / std::filesystem::path(std::string("new") + std::to_string(m_Project->GetScenes().size()) + std::string(".crscene"));
			
			std::ofstream file(path);
			file << " " << std::endl;
			file.close();

			// TODO(Jorben): Add a way to choose between 2D and 3D
			SceneProperties props;
			props.Name = std::string("New") + std::to_string(m_Project->GetScenes().size());
			props.Path = path;
			props.SceneType = SceneProperties::Type::_2D;

			m_Project->SaveScene();
			m_StartUp = true;

			m_Project->AddScene(props);
			m_Project->SetScene(props);
		}

		Panels::EndColours();
		ImGui::End();
	}

}