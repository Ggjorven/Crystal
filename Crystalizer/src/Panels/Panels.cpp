#include "Panels.hpp"

#include "Crystal/Core/Application.hpp"
#include "Crystal/Core/Events/Input/Input.hpp"
#include "Crystal/Utils/Utils.hpp"

#include "Editor.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui_internal.h>

namespace Crystal
{
	Panels::Panels(Ref<Project>& project)
		: m_Project(project), m_SelectedEntity(nullptr)
	{
		m_CheckerboardTex = Texture2D::Create("assets/textures/checkerboard.tga");
	}

	Panels::~Panels()
	{
	}

	void Panels::ObjectsWindow()
	{
		Panels::BeginColours();
		ImGui::Begin("Objects");

		for (ECS::Entity& entity : m_Project->GetEntities())
		{
			std::string name;

			ECS::TagComponent* tag = entity.GetComponent<ECS::TagComponent>();
			if (tag)
				name = "Entity - " + tag->Tag;
			else
				name = "Entity - " + std::to_string(entity.GetUUID());
			
			if (ImGui::CollapsingHeader(name.c_str(), nullptr)) // TODO(Jorben): Naming instead of UUID
			{
				m_SelectedEntity = &entity; // TODO(Jorben): Create a better system of selecting entities, because now you have to close the last entity before opening a new one
				
				if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
				{
					//Delete object
					if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
					{
						ImVec2 windowPos = ImGui::GetWindowPos();
						ImVec2 mainViewportPos = ImGui::GetMainViewport()->Pos;
						ImVec2 relativePos = { windowPos.x - mainViewportPos.x, windowPos.y - mainViewportPos.y };

						ImVec2 windowSize = ImGui::GetWindowSize();

						MousePosition pos = Crystal::Input::GetMousePosition();

						if (EditorLayer::InWindow(windowPos, windowSize, pos))
							ImGui::OpenPopup("Delete Object");
					}

					if (ImGui::BeginPopupContextItem("Delete Object")) // TODO(Jorben): Fix, now the other menu shows up instead of this one
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
			}
		}

		//New object
		if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
		{
			ImVec2 windowPos = ImGui::GetWindowPos();
			ImVec2 mainViewportPos = ImGui::GetMainViewport()->Pos;
			ImVec2 relativePos = { windowPos.x - mainViewportPos.x, windowPos.y - mainViewportPos.y };

			ImVec2 windowSize = ImGui::GetWindowSize();

			MousePosition pos = Crystal::Input::GetMousePosition();

			if (EditorLayer::InWindow(windowPos, windowSize, pos))
				ImGui::OpenPopup("New Object");
		}

		if (ImGui::BeginPopupContextItem("New Object"))
		{
			if (ImGui::MenuItem("Entity"))
			{
				ECS::Entity e(m_Project->GetStorage(), "New");
				m_Project->AddEntity(e);
			}

			if (ImGui::MenuItem("Camera (TODO)"))
			{
				// Handle action for Item 2
			}

			ImGui::EndPopup();
		}

		ImGui::End();
		Panels::EndColours();
	}

	void Panels::ObjectPropertiesWindow()
	{
		Panels::BeginColours();
		ImGui::Begin("Properties");

		if (m_SelectedEntity)
		{
			//New Component
			if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
			{
				ImVec2 windowPos = ImGui::GetWindowPos();
				ImVec2 mainViewportPos = ImGui::GetMainViewport()->Pos;
				ImVec2 relativePos = { windowPos.x - mainViewportPos.x, windowPos.y - mainViewportPos.y };

				ImVec2 windowSize = ImGui::GetWindowSize();

				MousePosition pos = Crystal::Input::GetMousePosition();

				if (EditorLayer::InWindow(windowPos, windowSize, pos))
				{
					//CR_TRACE("AAA");
					ImGui::OpenPopup("New Component");
				}
			}

			if (ImGui::BeginPopupContextItem("New Component"))
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

				ImGui::EndPopup();
			}

			ECS::TagComponent* tag = m_SelectedEntity->GetComponent<ECS::TagComponent>();
			if (tag)
			{
				if (ImGui::CollapsingHeader("TagComponent", nullptr, ImGuiTreeNodeFlags_DefaultOpen)) // TODO(Jorben): Naming instead of UUID
				{
					ImGui::Text("Tag:");
					ImGui::SameLine();
					ImGui::Text(tag->Tag.c_str());
				}
				ImGui::Spacing();
			}

			ECS::TransformComponent* tc = m_SelectedEntity->GetComponent<ECS::TransformComponent>();
			if (tc)
			{
				ImGui::Spacing();
				if (ImGui::CollapsingHeader("TransformComponent", nullptr, ImGuiTreeNodeFlags_DefaultOpen)) // TODO(Jorben): Naming instead of UUID
				{
					ImGui::DragFloat3("Position", glm::value_ptr(tc->Position), 0.01f); // TODO(Jorben): Update speed when Editor camera is created
					ImGui::DragFloat3("Size", glm::value_ptr(tc->Size), 0.01f); // TODO(Jorben): Update speed when Editor camera is created
					ImGui::DragFloat("Rotation", &tc->Rotation, 0.01f); // TODO(Jorben): Update speed when Editor camera is created
				}
				ImGui::Spacing();
			}

			ECS::Renderer2DComponent* r2d = m_SelectedEntity->GetComponent<ECS::Renderer2DComponent>();
			if (r2d)
			{
				ImGui::Spacing();
				if (ImGui::CollapsingHeader("Renderer2DComponent", nullptr, ImGuiTreeNodeFlags_DefaultOpen)) // TODO(Jorben): Naming instead of UUID
				{
					ImGui::ColorEdit4("Colour", glm::value_ptr(r2d->Colour));
					TexturePanel("Texture", r2d->Texture, &r2d->UseTexture);
				}
				ImGui::Spacing();
			}
		}

		ImGui::End();
		Panels::EndColours();
	}

	void Panels::TexturePanel(const std::string_view& name, Ref<Texture2D>& changeAbleTexture, bool* useTexture)
	{
		Panels::BeginColours();
		//if (ImGui::CollapsingHeader(name.data(), nullptr, ImGuiTreeNodeFlags_DefaultOpen))
		//{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
			ImGui::Image(changeAbleTexture ? (void*)changeAbleTexture->GetRendererID() : (void*)m_CheckerboardTex->GetRendererID(), ImVec2(32, 32), { 0, 1 }, { 1, 0 });
			ImGui::PopStyleVar();

			if (ImGui::IsItemHovered())
			{
				if (changeAbleTexture) //Texture is set
				{
					ImGui::BeginTooltip();

					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 17.5f);
					ImGui::TextUnformatted(changeAbleTexture->GetPath().c_str());
					ImGui::PopTextWrapPos();
					ImGui::Image((void*)changeAbleTexture->GetRendererID(), ImVec2(192, 192), { 0, 1 }, { 1, 0 });

					ImGui::EndTooltip();
				}

				if (ImGui::IsItemClicked()) //Open a new file/texture
				{
					std::string filename = Utils::OpenFile("");
					CR_TRACE("Selected file: {0}", filename);

					if (filename != "")
					{
						changeAbleTexture.reset(); changeAbleTexture = Texture2D::Create(filename);
					}
				}
			}
			
			if (useTexture) //if not nullptr
			{
				ImGui::SameLine();

				std::string strName = name.data();

				ImGui::BeginGroup();

				std::string use = "Use##" + strName;
				ImGui::Checkbox(use.c_str(), useTexture);

				ImGui::EndGroup();
			}
			//ImGui::SameLine();
			//
			//std::string colour = "Colour##" + strName;
			//ImGui::ColorEdit3(colour.c_str(), glm::value_ptr(m_AlbedoInput.Color), ImGuiColorEditFlags_NoInputs);
			
		//}
		Panels::EndColours();
	}

	//Colours
	void Panels::BeginColours()
	{
	}

	void Panels::EndColours()
	{
	}

}