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

	void Panels::SceneSettingsWindow(bool* sceneOpen)
	{
		const Window& window = Application::Get().GetWindow();

		Panels::BeginColours();

		static bool projWindow = true;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.0f, 4.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.09f, 0.09f, 0.09f, 1.0f));

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking;
		ImGui::Begin("Scene Settings", sceneOpen, flags);

		auto scene = Project::GetCurrentProject()->GetCurrentScene();

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;
		// C# Assemblies
		if (ImGui::TreeNodeEx("Assemblies", treeNodeFlags))
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			ImGui::Spacing();

			for (int i = 0; i < scene->GetStorage().s_AssemblyPaths.size(); i++)
			{
				auto& assembly = scene->GetStorage().s_AssemblyPaths[i];

				ImGui::Text(std::string(std::string("Assembly #") + std::to_string((i + 1)) + std::string(" ")).c_str());
				ImGui::SameLine();
				std::filesystem::path scriptDir = Project::GetCurrentProject()->GetScriptsDir();
				ImGui::TextDisabled((scriptDir / assembly).string().c_str());

				ImGui::SameLine();
				if (ImGui::Button("Remove"))
				{
					scene->GetStorage().s_AssemblyPaths.erase(scene->GetStorage().s_AssemblyPaths.begin() + i);
					scene->GetStorage().ReloadAssemblies();
				}
			}
			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::Dummy(ImVec2(ImGui::GetCurrentWindow()->Size.x / 2.0f - ImGui::CalcTextSize("Add New Assembly").x, 0.0f));
			ImGui::SameLine();
			if (ImGui::Button("Add New Assembly"))
			{
				std::string file = Utils::OpenFile(".dll\0*.dll", Project::GetCurrentProject()->GetProjectDir().string().c_str());

				if (!file.empty())
				{
					std::filesystem::path projDir = Project::GetCurrentProject()->GetProjectDir();
					std::filesystem::path scriptDir = Project::GetCurrentProject()->GetScriptsDir();

					Project::GetCurrentProject()->GetCurrentScene()->GetStorage().AddPath(std::filesystem::relative(file, projDir / scriptDir));
					Project::GetCurrentProject()->GetCurrentScene()->GetStorage().LoadAssembly(file);
				}
			}

			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Additional Settings", treeNodeFlags))
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			ImGui::Spacing();

			if (ImGui::ColorEdit4("Clear colour", &scene->GetClearColour().X))
			{
				RendererCommand::SetClearColour(Vec4<float>(scene->GetClearColour()));
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