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

	template<typename T>
	static void HandleComponentOptions(UI::ComponentOptions& co, CR_UUID uuid)
	{
		auto& scene = Project::GetCurrentProject()->GetCurrentScene();
		if (co.Remove)
		{
			scene->GetStorage().RemoveComponent<T>(uuid);
		}
			
	}

	void Panels::ObjectPropertiesWindow()
	{
		if (m_StartUp)
		{
			if (m_Project->GetCurrentScene()->GetEntities().size() > 0) 
				m_SelectedEntity = m_Project->GetCurrentScene()->GetEntities()[0];
			m_StartUp = false;
		}

		Panels::BeginColours();
		ImGui::Begin("Properties", (bool*)0, ImGuiWindowFlags_NoScrollbar);

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
					if (!m_SelectedEntity->HasComponent<ECS::TagComponent>() && ImGui::MenuItem("Tag"))
					{
						m_SelectedEntity->AddComponent<ECS::TagComponent>();
					}

					if (!m_SelectedEntity->HasComponent<ECS::TransformComponent>() && ImGui::MenuItem("Transform"))
					{
						m_SelectedEntity->AddComponent<ECS::TransformComponent>();
					}

					if (!m_SelectedEntity->HasComponent<ECS::Renderer2DComponent>() && ImGui::MenuItem("Renderer2D"))
					{
						m_SelectedEntity->AddComponent<ECS::Renderer2DComponent>();
					}

					if (!m_SelectedEntity->HasComponent<ECS::ColliderComponent>() && ImGui::MenuItem("Collider"))
					{
						m_SelectedEntity->AddComponent<ECS::ColliderComponent>();
					}

					if (!m_SelectedEntity->HasComponent<ECS::ScriptComponent>() && ImGui::MenuItem("Script"))
					{
						auto& script = m_SelectedEntity->AddComponent<ECS::ScriptComponent>();
						script.Script->SetUUID(m_SelectedEntity->GetUUID());
					}
					ImGui::EndMenu();
				}

				ImGui::EndPopup();
			}

			if (m_SelectedEntity->HasComponent<ECS::TagComponent>())
			{
				auto& tag = m_SelectedEntity->GetComponent<ECS::TagComponent>();
				UI::ComponentOptions co;
				if (UI::BeginECSComponent("TagComponent", co, s_Icons[(int)Icon::Tag]))
				{
					ImGui::Text("Tag:");
					ImGui::SameLine();

					static char buffer[256];
					strcpy_s(buffer, sizeof(buffer), tag.Tag.c_str());
					if (ImGui::InputText("##TagInput", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
						tag.Tag = buffer;
				}
				HandleComponentOptions<ECS::TagComponent>(co, m_SelectedEntity->GetUUID()); 
			}

			if (m_SelectedEntity->HasComponent<ECS::TransformComponent>())
			{
				auto& tc = m_SelectedEntity->GetComponent<ECS::TransformComponent>();
				UI::ComponentOptions co;
				if (UI::BeginECSComponent("TransformComponent", co, s_Icons[(int)Icon::Transform]))
				{
					UI::Vector3("Position", tc.Position, Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 1.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 0.0f, 1.0f, 1.0f));
					UI::Vector3("Size", tc.Size, Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 1.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 0.0f, 1.0f, 1.0f));
					/* // TODO(Jorben): Add rotation back here and add it in Renderer2D
					ImGui::Text("Rotation: ");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(150);
					ImGui::DragFloat("##Rotation", &tc->Rotation, 1.0f, 0.0f, 0.0f, "%.1f");
					*/
				}
				HandleComponentOptions<ECS::TransformComponent>(co, m_SelectedEntity->GetUUID());
			}

			if (m_SelectedEntity->HasComponent<ECS::Renderer2DComponent>())
			{
				auto& r2d = m_SelectedEntity->GetComponent<ECS::Renderer2DComponent>();
				UI::ComponentOptions co;
				if (UI::BeginECSComponent("Renderer2DComponent", co, s_Icons[(int)Icon::Renderer2D])) // TODO(Jorben): Add right click enabled/disabled functionality
				{
					//ImGui::Checkbox("Enabled", &r2d->Enable);
					TexturePanel("Texture", r2d.Texture, &r2d.UseTexture);

					ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
					
					ImGui::SameLine();
					ImGui::Dummy(ImVec2(50.0f, 0.0f));
					ImGui::SameLine();

					UI::Tools::SetContextFontSize(2.f);
					ImGui::ColorEdit4("Colour", r2d.Colour.GetData(), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip);
					UI::Tools::SetContextFontSize(0.0f);

					if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
					{
						ImGui::OpenPopup("ColorPickerPopup");
					}

					if (ImGui::BeginPopup("ColorPickerPopup"))
					{
						ImGui::ColorPicker4("ColorPicker", r2d.Colour.GetData());
						ImGui::EndPopup();
					}

					ImGui::PopStyleVar(1);

					ImGui::SameLine();
					ImGui::Checkbox("Use", &r2d.UseColour);

				}
				HandleComponentOptions<ECS::Renderer2DComponent>(co, m_SelectedEntity->GetUUID());
			}

			if (m_SelectedEntity->HasComponent<ECS::ColliderComponent>())
			{
				auto& col = m_SelectedEntity->GetComponent<ECS::ColliderComponent>();
				UI::ComponentOptions co;
				if (UI::BeginECSComponent("ColliderComponent", co, s_Icons[(int)Icon::Renderer2D])) // TODO(Jorben): Add right click enabled/disabled functionality
				{
					static bool AABB = (col.AABB ? true : false);
					//static bool ... = false;
					ImGui::Dummy(ImVec2(10.0f, 0.0f));
					ImGui::SameLine();
					if (ImGui::RadioButton("AABB", AABB))
					{
						col.AABB = CreateRef<AABBCollider>();

						AABB = true;
					}

					if (AABB)
					{
						// TODO(Jorben): Add position and linking to Transforms
						//if (ImGui::Checkbox("##Linked1")) 
						UI::Vector3("Position", col.AABB->GetPosition(), Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 1.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 0.0f, 1.0f, 1.0f));
						UI::Vector3("Size", col.AABB->GetSize(), Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 1.0f, 0.0f, 1.0f), Vec4<float>(0.0f, 0.0f, 1.0f, 1.0f));
					}
				}
				HandleComponentOptions<ECS::ColliderComponent>(co, m_SelectedEntity->GetUUID());
			}

			if (m_SelectedEntity->HasComponent<ECS::ScriptComponent>())
			{
				auto& sc = m_SelectedEntity->GetComponent<ECS::ScriptComponent>();

				// Note(Jorben): Check if components have not been sent to the ScriptComponent
				ComponentList& cl = sc.Script->GetComponents();
				if (!cl.TagComponent && m_SelectedEntity->HasComponent<ECS::TagComponent>())
				{
					sc.Script->AddTagComponent();
					cl.TagComponent = true;
				}

				if (!cl.TransformComponent && m_SelectedEntity->HasComponent<ECS::TransformComponent>())
				{
					sc.Script->AddTransformComponent();
					cl.TransformComponent = true;
				}

				UI::ComponentOptions co;
				if (UI::BeginECSComponent("ScriptComponent", co, s_Icons[(int)Icon::Script])) // TODO(Jorben): Add right click enabled/disabled functionality
				{
					ImGui::BulletText("Class:");
					ImGui::SameLine();

					static char buffer[256];
					strcpy_s(buffer, sizeof(buffer), sc.Script->GetClass().c_str());

					ImGui::SetNextItemWidth(150);
					if (ImGui::InputText("##ClassName", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
						sc.Script->SetClass(buffer);

					// Display ValueFields
					sc.Script->DisplayValueFields();
				}
				HandleComponentOptions<ECS::ScriptComponent>(co, m_SelectedEntity->GetUUID());
			}
		}

		Panels::EndColours();
		ImGui::End();
	}

}