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

	void Panels::ObjectsWindow()
	{
		Panels::BeginColours();
		ImGui::Begin("Objects");

		std::string fps = std::string("FPS(average): ") + std::to_string((int32_t)Application::Get().GetWindow().GetFPS());
		ImGui::Text(fps.c_str());

		static bool showDelete = false;
		static CR_UUID deleteUUID = 0;

		//New object
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ImVec2 windowPos = ImGui::GetCurrentWindow()->Pos;
			ImVec2 mainViewportPos = ImGui::GetMainViewport()->Pos;
			ImVec2 relativePos = { windowPos.x - mainViewportPos.x, windowPos.y - mainViewportPos.y };

			ImVec2 windowSize = ImGui::GetCurrentWindow()->Size;

			MousePosition pos = Crystal::Input::GetMousePosition();

			if (EditorLayer::InWindow(relativePos, windowSize, pos))
			{
				ImGui::OpenPopup("New Object");

				showDelete = false;
				deleteUUID = 0;
			}
		}

		for (Ref<ECS::Entity>& entity : m_Project->GetCurrentScene()->GetEntities())
		{
			//Naming
			std::string name;
			{
				auto& tag = entity->GetComponent<ECS::TagComponent>();
				if (entity->HasComponent<ECS::TagComponent>() && !tag.Tag.empty())
					name = std::string("- ") + tag.Tag;
				else
					name = std::string("- ") + std::to_string(entity->GetUUID());
			}

			//Create a selectable entity
			bool selected = false;
			if (m_SelectedEntity)
				selected = (entity->GetUUID() == m_SelectedEntity->GetUUID());

			if (ImGui::Selectable(name.c_str(), selected, ImGuiSelectableFlags_SpanAllColumns))
			{
				m_SelectedEntity = entity;
			}

			//Check for right-click/delete
			if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			{
				showDelete = true;
				deleteUUID = entity->GetUUID();
			}
		}
		// TODO(Jorben): Add a better way to set the selected entity
		// TODO(Jorben): Fix selectionmanager crash
		//if (s_ButtonState == ButtonState::Play) // Note(Jorben): The button shows play when not running
			//SelectionManager::Get()->SetSelected(m_SelectedEntity);

		//Actual pop-up
		if (ImGui::BeginPopupContextItem("New Object"))
		{
			// New Object
			if (ImGui::BeginMenu(" New        "))
			{
				if (ImGui::MenuItem("Entity"))
				{
					Ref<ECS::Entity> e = ECS::Entity::Create(m_Project->GetCurrentScene()->GetStorage(), "New");
					m_Project->GetCurrentScene()->AddEntity(e);
					m_SelectedEntity = e;
				}

				if (ImGui::BeginMenu("Camera")) // TODO(Jorben): Actually create a camera
				{
					if (ImGui::MenuItem("Orthographic"))
					{
						Ref<ECS::Entity> e = ECS::Entity::Create(m_Project->GetCurrentScene()->GetStorage(), "New");

						auto& tag = e->AddComponent<ECS::TagComponent>();
						tag.Tag = "OrthoGraphic-Camera";

						e->AddComponent<ECS::CameraComponent2D>();

						m_Project->GetCurrentScene()->AddEntity(e);
						m_SelectedEntity = e;
					}

					if (ImGui::MenuItem("Perspective"))
					{
						Ref<ECS::Entity> e = ECS::Entity::Create(m_Project->GetCurrentScene()->GetStorage(), "New");

						auto& tag = e->AddComponent<ECS::TagComponent>();
						tag.Tag = "Perspective-Camera";

						e->AddComponent<ECS::CameraComponent3D>();

						m_Project->GetCurrentScene()->AddEntity(e);
						m_SelectedEntity = e;
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			// Delete Object
			if (showDelete && ImGui::MenuItem(" Delete"))
			{
				auto& entities = m_Project->GetCurrentScene()->GetEntities();
				for (int i = 0; i < entities.size(); i++)
				{
					if (entities[i]->GetUUID() == deleteUUID)
					{
						m_Project->GetCurrentScene()->GetStorage().DeleteEntity(entities[i]->GetUUID());
						entities.erase(entities.begin() + i);
						
						if (entities.size() > 0)
							m_SelectedEntity = entities[i - 1];
						else
							m_SelectedEntity = nullptr;

						break;
					}
				}
				showDelete = false;
			}
			ImGui::EndMenu();
		}

		Panels::EndColours();
		ImGui::End();
	}
}