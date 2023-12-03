#include "Panels.hpp"

#include "Crystal/Core/Application.hpp"
#include "Crystal/Core/Events/Input/Input.hpp"
#include "Crystal/Utils/Utils.hpp"

#include "Crystal/UI/UICore.hpp"
#include "Crystal/UI/UITools.hpp"

#include "Editor.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_internal.h>

namespace Crystal
{

	void Panels::ProjectSettingsWindow(bool* projOpen)
	{
		const Window& window = Application::Get().GetWindow();

		Panels::BeginColours();
		
		static bool projWindow = true;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.0f, 4.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.09f, 0.09f, 0.09f, 1.0f));
		
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking;
		ImGui::Begin("Project Settings", projOpen, flags);

		auto scene = Project::GetCurrentProject()->GetCurrentScene();

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;
		
		if (ImGui::TreeNodeEx("Project Directories", treeNodeFlags))
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			Project* project = Project::GetCurrentProject();

			ImGui::Spacing();

			ImGui::Text("Assets Dir: ");
			ImGui::SameLine();
			ImGui::TextDisabled(project->GetAssetDir().string().c_str());
			ImGui::SameLine();
			if (ImGui::Button("...##Assets"))
			{
				std::string dir = Utils::OpenDirectory(project->GetProjectDir().string().c_str());

				if (!dir.empty())
				{
					std::filesystem::path relPath = std::filesystem::relative(std::filesystem::path(dir), project->GetProjectDir());
					project->SetAssetDir(relPath);
				}
			}

			ImGui::Text("Scene Dir: ");
			ImGui::SameLine();
			ImGui::TextDisabled(project->GetSceneDir().string().c_str());
			ImGui::SameLine();
			if (ImGui::Button("...##Scenes"))
			{
				std::string dir = Utils::OpenDirectory(project->GetProjectDir().string().c_str());

				if (!dir.empty())
				{
					std::filesystem::path relPath = std::filesystem::relative(std::filesystem::path(dir), project->GetProjectDir());
					project->SetSceneDir(relPath);
				}
			}

			ImGui::Text("Scripts Dir: ");
			ImGui::SameLine();
			ImGui::TextDisabled(project->GetScriptsDir().string().c_str());
			ImGui::SameLine();
			if (ImGui::Button("...##Scripts"))
			{
				std::string dir = Utils::OpenDirectory(project->GetProjectDir().string().c_str());

				if (!dir.empty())
				{
					std::filesystem::path relPath = std::filesystem::relative(std::filesystem::path(dir), project->GetProjectDir());
					project->SetScriptsDir(relPath);
				}
			}

			ImGui::Spacing();

			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Additional Settings", treeNodeFlags))
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			ImGui::Spacing();

			static bool wireFrame = false;
			if (ImGui::Checkbox("Wireframe", &wireFrame))
			{
				RendererCommand::EnableWireFrame(wireFrame);
			}

			ImGui::Spacing();
			
			ImGui::TreePop();
		}

		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(1);

		ImGui::End();

		Panels::EndColours();
	}

}