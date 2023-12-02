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
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking;
		ImGui::Begin("Project Settings", projOpen, flags);

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.0f, 4.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.08f, 0.08f, 0.08f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.08f, 0.08f, 0.08f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.08f, 0.08f, 0.08f, 1.0f));

		auto scene = Project::GetCurrentProject()->GetCurrentScene();

		// C# Assemblies
		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;
		
		if (ImGui::TreeNodeEx("Assemblies", treeNodeFlags))
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			for (int i = 0; i < scene->GetStorage().s_AssemblyPaths.size(); i++)
			{
				auto& assembly = scene->GetStorage().s_AssemblyPaths[i];

				ImGui::Text(std::string(std::string("Assembly #") + std::to_string(i) + std::string(" ")).c_str());
				ImGui::SameLine();
				ImGui::Text(assembly.string().c_str());

				ImGui::SameLine();
				if (ImGui::Button("Remove"))
				{
					scene->GetStorage().s_AssemblyPaths.erase(scene->GetStorage().s_AssemblyPaths.begin() + i);
					scene->GetStorage().ReloadAssemblies();
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

			static bool wireFrame = false;
			if (ImGui::Checkbox("Wireframe", &wireFrame))
			{
				RendererCommand::EnableWireFrame(wireFrame);
			}

			ImGui::TreePop();
		}

		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(3);

		ImGui::End();
		Panels::EndColours();
	}

}