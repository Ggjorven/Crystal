#include "Panels.hpp"

#include "Crystal/Core/Application.hpp"
#include "Crystal/Core/Events/Input/Input.hpp"
#include "Crystal/Utils/Utils.hpp"

#include "Crystal/UI/UICore.hpp"

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

				if (EditorLayer::InWindow(relativePos, ImGui::GetCurrentWindow()->Size, Crystal::Input::GetMousePosition()))
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
				if (UI::BeginECSComponent("TagComponent", s_Icons[(int)Icon::Tag]))
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
				if (UI::BeginECSComponent("TransformComponent", s_Icons[(int)Icon::Transform]))
				{
					UI::Vector3("Position", tc->Position, Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 1.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 0.0f, 1.0f, 1.0f));
					UI::Vector3("Size", tc->Size, Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 1.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 0.0f, 1.0f, 1.0f));
					/* // TODO(Jorben): Add rotation back here and add it in Renderer2D
					ImGui::Text("Rotation: ");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(150);
					ImGui::DragFloat("##Rotation", &tc->Rotation, 1.0f, 0.0f, 0.0f, "%.1f");
					*/
				}
			}

			ECS::Renderer2DComponent* r2d = m_SelectedEntity->GetComponent<ECS::Renderer2DComponent>();
			if (r2d)
			{
				if (UI::BeginECSComponent("Renderer2DComponent", s_Icons[(int)Icon::Renderer2D])) // TODO(Jorben): Add right click enabled/disabled functionality
				{
					//ImGui::Checkbox("Enabled", &r2d->Enable);
					ImGui::ColorEdit4("Colour", r2d->Colour.GetData(), ImGuiColorEditFlags_Uint8);
					TexturePanel("Texture", r2d->Texture, &r2d->UseTexture);
				}
			}

			ECS::ScriptComponent* sc = m_SelectedEntity->GetComponent<ECS::ScriptComponent>();
			if (sc)
			{
				if (UI::BeginECSComponent("ScriptComponent", s_Icons[(int)Icon::Script])) // TODO(Jorben): Add right click enabled/disabled functionality
				{
					ImGui::BulletText(sc->Path.filename().string().c_str());

					ImGui::SameLine();
					if (ImGui::Button("Reload"))
						sc->Script.SetDLL(sc->Path);

					ImGui::SameLine();
					if (ImGui::Button("..."))
					{
						std::string filename = Utils::OpenFile("");

						if (!filename.empty())
						{
							sc->Path = filename;
							sc->Script.SetDLL(filename);
						}
					}

					ImGui::BulletText("Class:");
					ImGui::SameLine();

					static char buffer[256];
					strcpy_s(buffer, sizeof(buffer), sc->Script.GetClass().c_str());

					ImGui::SetNextItemWidth(160);
					if (ImGui::InputText("##ClassName", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
						sc->Script.SetClass(buffer);
				}
			}
		}

		ImGui::End();
		Panels::EndColours();
	}

}