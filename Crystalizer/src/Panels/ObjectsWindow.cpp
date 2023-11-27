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
					name = std::string("Entity - ") + std::string(tag.Tag);
				else
					name = std::string("Entity - ") + std::to_string(entity->GetUUID());
			}

			//Create a selectable entity
			if (ImGui::Selectable(name.c_str(), false, ImGuiSelectableFlags_SpanAllColumns)) // TODO(Jorben): Make it so you can see that it's selected so replace 'false'
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

		//Actual pop-up
		if (ImGui::BeginPopupContextItem("New Object"))
		{

			if (ImGui::BeginMenu(" New        "))
			{
				if (ImGui::MenuItem("Entity"))
				{
					Ref<ECS::Entity> e = ECS::Entity::Create(m_Project->GetCurrentScene()->GetStorage(), "New");
					m_Project->GetCurrentScene()->AddEntity(e);
				}

				if (ImGui::MenuItem("Camera")) // TODO(Jorben): Actually create a camera
				{
					CR_CORE_TRACE("TODO");
				}
				ImGui::EndMenu();
			}

			if (showDelete && ImGui::MenuItem(" Delete"))
			{
				auto& entities = m_Project->GetCurrentScene()->GetEntities();
				for (int i = 0; i < entities.size(); i++)
				{
					if (entities[i]->GetUUID() == deleteUUID)
					{
						entities.erase(entities.begin() + i);
						break;
					}
				}
				showDelete = false;
			}
			ImGui::EndMenu();
		}

		ImGui::End();
		Panels::EndColours();
	}
}