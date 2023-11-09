#include "Panels.hpp"

#include "Crystal/Core/Application.hpp"
#include "Crystal/Core/Events/Input/Input.hpp"
#include "Crystal/Utils/Utils.hpp"

#include "Editor.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_internal.h>

namespace Crystal
{

	void Panels::ObjectPropertiesWindow()
	{
		Panels::BeginColours();
		ImGui::Begin("Properties");

		if (m_SelectedEntity)
		{
			//New Component
			if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
			{
				ImVec2 windowPos = ImGui::GetCurrentWindow()->Pos;
				ImVec2 mainViewportPos = ImGui::GetMainViewport()->Pos;
				ImVec2 relativePos = { windowPos.x - mainViewportPos.x, windowPos.y - mainViewportPos.y };

				ImVec2 windowSize = ImGui::GetCurrentWindow()->Size;

				MousePosition pos = Crystal::Input::GetMousePosition();

				if (EditorLayer::InWindow(relativePos, windowSize, pos))
					ImGui::OpenPopup("New Component");
			}

			if (ImGui::BeginPopupContextItem("New Component"))
			{
				if (ImGui::BeginMenu(" Add        "))
				{
					if (!m_SelectedEntity->GetComponent<ECS::TagComponent>() && ImGui::MenuItem("Tag"))
					{
						m_SelectedEntity->AddComponent<ECS::TagComponent>();
					}

					if (!m_SelectedEntity->GetComponent<ECS::TransformComponent>() && ImGui::MenuItem("Transform"))
					{
						m_SelectedEntity->AddComponent<ECS::TransformComponent>();
					}

					if (!m_SelectedEntity->GetComponent<ECS::Renderer2DComponent>() && ImGui::MenuItem("Renderer2D"))
					{
						m_SelectedEntity->AddComponent<ECS::Renderer2DComponent>();
					}

					if (!m_SelectedEntity->GetComponent<ECS::ScriptComponent>() && ImGui::MenuItem("Script"))
					{
						m_SelectedEntity->AddComponent<ECS::ScriptComponent>();
						m_SelectedEntity->GetComponent<ECS::ScriptComponent>()->Script.SetUUID(m_SelectedEntity->GetUUID());
					}
					ImGui::EndMenu();
				}

				ImGui::EndPopup();
			}

			ECS::TagComponent* tag = m_SelectedEntity->GetComponent<ECS::TagComponent>();
			if (tag)
			{
				if (ImGui::CollapsingHeader("TagComponent", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Text("Tag:");
					ImGui::SameLine();

					static char buffer[256]; 
					strcpy_s(buffer, sizeof(buffer), tag->Tag.c_str());
					if (ImGui::InputText("##TagInput", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
						tag->Tag = buffer;
				}
			}

			ECS::TransformComponent* tc = m_SelectedEntity->GetComponent<ECS::TransformComponent>();
			if (tc)
			{
				if (ImGui::CollapsingHeader("TransformComponent", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::DragFloat3("Position", glm::value_ptr(tc->Position), 1.0f, 0.0f, 0.0f, "%.0f");
					ImGui::DragFloat3("Size", glm::value_ptr(tc->Size), 1.0f, 0.0f, 0.0f, "%.0f");
					ImGui::DragFloat("Rotation", &tc->Rotation, 1.0f, 0.0f, 0.0f, "%.0f");
				}
			}

			ECS::Renderer2DComponent* r2d = m_SelectedEntity->GetComponent<ECS::Renderer2DComponent>();
			if (r2d)
			{
				if (ImGui::CollapsingHeader("Renderer2DComponent", nullptr, ImGuiTreeNodeFlags_DefaultOpen)) // TODO(Jorben): Add right click enabled/disabled functionality
				{
					ImGui::Checkbox("Enabled", &r2d->Enable);
					ImGui::ColorEdit4("Colour", glm::value_ptr(r2d->Colour), ImGuiColorEditFlags_Uint8);
					TexturePanel("Texture", r2d->Texture, &r2d->UseTexture);
				}
			}

			ECS::ScriptComponent* sc = m_SelectedEntity->GetComponent<ECS::ScriptComponent>();
			if (sc)
			{
				if (ImGui::CollapsingHeader("ScriptComponent", nullptr, ImGuiTreeNodeFlags_DefaultOpen)) // TODO(Jorben): Add right click enabled/disabled functionality
				{
					ImGui::Text("File:");
					ImGui::SameLine();
					// TODO(Jorben): Adding a script based on file explorer
					static char Scriptbuffer[256];
					strcpy_s(Scriptbuffer, sizeof(Scriptbuffer), sc->Path.string().c_str());
					if (ImGui::InputText("##Script", Scriptbuffer, sizeof(Scriptbuffer), ImGuiInputTextFlags_EnterReturnsTrue))
					{
						sc->Path = Scriptbuffer;
						sc->Script.SetDLL(Scriptbuffer);
					}

					ImGui::Text("Class:");
					ImGui::SameLine();

					static char buffer[256];
					strcpy_s(buffer, sizeof(buffer), sc->Script.GetClass().c_str());
					if (ImGui::InputText("##ClassName", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
						sc->Script.SetClass(buffer);

					// TODO(Jorben): Make better
					if (ImGui::Button("OnCreate"))
					{
						sc->Script.OnCreate();
					}

					if (ImGui::Button("OnUpdate"))
					{
						Timestep ts(0.0f);
						sc->Script.OnUpdate(ts);
					} 

				}
			}
		}

		ImGui::End();
		Panels::EndColours();
	}

}