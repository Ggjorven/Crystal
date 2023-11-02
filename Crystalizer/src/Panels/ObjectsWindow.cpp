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

		for (ECS::Entity& entity : m_Project->GetEntities())
		{
			//Naming
			std::string name;
			{
				ECS::TagComponent* tag = entity.GetComponent<ECS::TagComponent>();
				if (tag && !tag->Tag.empty())
					name = "Entity - " + tag->Tag;
				else
					name = "Entity - " + std::to_string(entity.GetUUID());
			}

			//Create a selectable entity
			if (ImGui::Selectable(name.c_str(), false, ImGuiSelectableFlags_SpanAllColumns)) // TODO(Jorben): Make it so you can see that it's selected so replace 'false'
			{
				m_SelectedEntity = &entity; 
			}

			//Check for right-click/delete
			/*
			if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			{
				CR_CORE_TRACE("AAA");

				ImGui::OpenPopup("Delete-Object");
				if (ImGui::BeginPopupContextItem("Delete-Object")) // TODO(Jorben): Fix, now the other menu shows up instead of this one
				{
					if (ImGui::MenuItem("Delete"))
					{

						//auto& entities = m_Project->GetEntities();
						//for (int i = 0; i < entities.size(); i++)
						//{
						//	if (entities[i].GetUUID() == entity.GetUUID())
						//	{
						//		entities.erase(entities.begin() + i);
						//		break;
						//	}
						//}
					}
					ImGui::EndPopup();
				}
			}
			*/
		}

		//New object
		if (ImGui::IsMouseReleased(ImGuiMouseButton_Right)) 
		{
			ImVec2 windowPos = ImGui::GetCurrentWindow()->Pos;
			ImVec2 mainViewportPos = ImGui::GetMainViewport()->Pos;
			ImVec2 relativePos = { windowPos.x - mainViewportPos.x, windowPos.y - mainViewportPos.y };

			ImVec2 windowSize = ImGui::GetCurrentWindow()->Size;

			MousePosition pos = Crystal::Input::GetMousePosition();

			if (EditorLayer::InWindow(relativePos, windowSize, pos))
				ImGui::OpenPopup("New Object");
		}

		if (ImGui::BeginPopupContextItem("New Object"))
		{
			if (ImGui::BeginMenu(" New        "))
			{
				if (ImGui::MenuItem("Entity"))
				{
					ECS::Entity e(m_Project->GetStorage(), "New");
					m_Project->AddEntity(e);
				}

				if (ImGui::MenuItem("Camera")) // TODO(Jorben): Actually create a camera
				{
					CR_CORE_TRACE("TODO");
				}
				ImGui::EndMenu();
			}
			ImGui::Separator();
			if (ImGui::BeginMenu(" Delete        "))
			{
				for (ECS::Entity& entity : m_Project->GetEntities())
				{
					//Naming
					std::string name;
					{
						ECS::TagComponent const* tag = entity.GetComponent<ECS::TagComponent>();
						if (tag && !tag->Tag.empty())
							name = "Entity - " + tag->Tag;
						else
							name = "Entity - " + std::to_string(entity.GetUUID());
					}

					//Create a menu
					if (ImGui::Selectable(name.c_str())) // TODO
					{
						CR_CORE_TRACE("Delete {0}", name);

						std::vector<ECS::Entity>& entities = m_Project->GetEntities();
						for (int i = 0; i < entities.size(); i++)
						{
							if (entities[i].GetUUID() == entity.GetUUID())
							{
								entities.erase(entities.begin() + i);
								break;
							}
						}
					}
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		ImGui::End();
		Panels::EndColours();
	}
}