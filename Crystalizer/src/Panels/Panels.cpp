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
	Panels::Panels(Ref<Project>& project)
		: m_Project(project), m_SelectedEntity(nullptr)
	{
		std::string path = Utils::GetEnviromentVariable("CRYSTAL_DIR");
		m_CheckerboardTex = Texture2D::Create(path + "\\Crystalizer\\assets\\textures\\Checkerboard.tga");
		m_ButtonTex = Texture2D::Create(path + "\\Crystalizer\\assets\\textures\\Checkerboard.tga");
	}

	Panels::~Panels()
	{
	}

	void Panels::Vector3(const std::string& label, float& value, const ImVec4& colourN, const ImVec4& colourH, const ImVec4& colourP, bool renderMultiSelect)
	{
		/* TODO(Jorben): ...
		{
			UI::ScopedStyle buttonFrame(ImGuiStyleVar_FramePadding, ImVec2(framePadding, 0.0f));
			UI::ScopedStyle buttonRounding(ImGuiStyleVar_FrameRounding, 1.0f);
			UI::ScopedColourStack buttonColours(ImGuiCol_Button, colourN,
				ImGuiCol_ButtonHovered, colourH,
				ImGuiCol_ButtonActive, colourP);

			UI::ScopedFont buttonFont(boldFont);

			UI::ShiftCursorY(2.0f);
			if (ImGui::Button(label.c_str(), buttonSize))
			{
				value = resetValue;
				modified = true;
			}
		}

		ImGui::SameLine(0.0f, outlineSpacing);
		ImGui::SetNextItemWidth(inputItemWidth);
		UI::ShiftCursorY(-2.0f);
		ImGui::PushItemFlag(ImGuiItemFlags_MixedValue, renderMultiSelect);
		bool wasTempInputActive = ImGui::TempInputIsActive(ImGui::GetID(("##" + label).c_str()));
		modified |= UI::DragFloat(("##" + label).c_str(), &value, 0.1f, 0.0f, 0.0f, "%.2f", 0);

		// NOTE(Peter): Ugly hack to make tabbing behave the same as Enter (e.g marking it as manually modified)
		if (modified && Input::IsKeyDown(KeyCode::Tab))
			manuallyEdited = true;

		if (ImGui::TempInputIsActive(ImGui::GetID(("##" + label).c_str())))
			modified = false;

		ImGui::PopItemFlag();

		if (wasTempInputActive)
			manuallyEdited |= ImGui::IsItemDeactivatedAfterEdit();
		*/
	}

	void Panels::TexturePanel(const std::string_view& name, Ref<Texture2D>& changeAbleTexture, bool* useTexture)
	{
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

				if (!filename.empty())
				{
					changeAbleTexture.reset(); changeAbleTexture = Texture2D::Create(filename);
				}
			}
		}
		if (useTexture) //if not nullptr
		{
			ImGui::SameLine();

			ImGui::BeginGroup();
			ImGui::Checkbox(std::string(std::string("Use##") + std::string(name.data())).c_str(), useTexture);
			ImGui::EndGroup();
		}
	}

	//Colours
	void Panels::BeginColours()
	{
		/*
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.14f, 0.36f, 0.41f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.19f, 0.51f, 0.59f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.19f, 0.51f, 0.58f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.12f, 0.30f, 0.34f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.27f, 0.77f, 0.86f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.19f, 0.51f, 0.58f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.19f, 0.51f, 0.58f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.19f, 0.51f, 0.58f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.22f, 0.62f, 0.70f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.19f, 0.51f, 0.58f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.17f, 0.55f, 0.64f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.26f, 0.64f, 0.72f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.25f, 0.71f, 0.81f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_SeparatorHovered, ImVec4(0.09f, 0.27f, 0.31f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_SeparatorActive, ImVec4(0.08f, 0.34f, 0.40f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_ResizeGrip, ImVec4(0.20f, 0.63f, 0.72f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, ImVec4(0.20f, 0.63f, 0.72f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, ImVec4(0.20f, 0.63f, 0.72f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.09f, 0.25f, 0.28f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(0.20f, 0.63f, 0.72f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.13f, 0.40f, 0.46f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_TabUnfocused, ImVec4(0.03f, 0.11f, 0.12f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive, ImVec4(0.34f, 0.88f, 1.00f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_DockingPreview, ImVec4(0.20f, 0.63f, 0.72f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImVec4(0.20f, 0.63f, 0.72f, 0.54f));
		ImGui::PushStyleColor(ImGuiCol_NavHighlight, ImVec4(0.20f, 0.63f, 0.72f, 0.54f));
		*/
		
		//Colours
		auto& colours = ImGui::GetStyle().Colors;
		colours[ImGuiCol_FrameBg] = ImVec4(0.14f, 0.36f, 0.41f, 0.54f);
		colours[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.51f, 0.59f, 0.54f);
		colours[ImGuiCol_FrameBgActive] = ImVec4(0.19f, 0.51f, 0.58f, 0.54f);
		colours[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.30f, 0.34f, 0.54f);
		colours[ImGuiCol_CheckMark] = ImVec4(0.27f, 0.77f, 0.86f, 1.00f);
		colours[ImGuiCol_SliderGrab] = ImVec4(0.19f, 0.51f, 0.58f, 0.54f);
		colours[ImGuiCol_SliderGrabActive] = ImVec4(0.19f, 0.51f, 0.58f, 0.54f);
		colours[ImGuiCol_Button] = ImVec4(0.19f, 0.51f, 0.58f, 0.54f);
		colours[ImGuiCol_ButtonHovered] = ImVec4(0.22f, 0.62f, 0.70f, 0.54f);
		colours[ImGuiCol_ButtonActive] = ImVec4(0.19f, 0.51f, 0.58f, 0.54f);
		colours[ImGuiCol_Header] = ImVec4(0.17f, 0.55f, 0.64f, 0.54f);
		colours[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.64f, 0.72f, 0.54f);
		colours[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.71f, 0.81f, 0.54f);
		colours[ImGuiCol_SeparatorHovered] = ImVec4(0.09f, 0.27f, 0.31f, 0.54f);
		colours[ImGuiCol_SeparatorActive] = ImVec4(0.08f, 0.34f, 0.40f, 0.54f);
		colours[ImGuiCol_ResizeGrip] = ImVec4(0.20f, 0.63f, 0.72f, 0.54f);
		colours[ImGuiCol_ResizeGripHovered] = ImVec4(0.20f, 0.63f, 0.72f, 0.54f);
		colours[ImGuiCol_ResizeGripActive] = ImVec4(0.20f, 0.63f, 0.72f, 0.54f);
		colours[ImGuiCol_Tab] = ImVec4(0.09f, 0.25f, 0.28f, 0.54f);
		colours[ImGuiCol_TabHovered] = ImVec4(0.20f, 0.63f, 0.72f, 0.54f);
		colours[ImGuiCol_TabActive] = ImVec4(0.13f, 0.40f, 0.46f, 0.54f);
		colours[ImGuiCol_TabUnfocused] = ImVec4(0.03f, 0.11f, 0.12f, 0.54f);
		colours[ImGuiCol_TabUnfocusedActive] = ImVec4(0.34f, 0.88f, 1.00f, 0.54f);
		colours[ImGuiCol_DockingPreview] = ImVec4(0.20f, 0.63f, 0.72f, 0.54f);
		colours[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.63f, 0.72f, 0.54f);
		colours[ImGuiCol_NavHighlight] = ImVec4(0.20f, 0.63f, 0.72f, 0.54f);

		colours[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.21f, 0.24f, 1.00f);
		colours[ImGuiCol_Separator] = ImVec4(0.24f, 0.71f, 0.81f, 0.54f);
		colours[ImGuiCol_DockingEmptyBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);



		//Main
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 10));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(15, 3));
		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(4, 2));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6, 4));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(4, 4));
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 21);
		ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 14);
		ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 10);

		//Borders
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, 1);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
		//ImGui::PushStyleVar(ImGuiStyleVar_TabBorderSize, 0);

		//Rounding
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12);
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 12);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12);
		ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 8);
		ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 9);
		ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 0);
		//ImGui::PushStyleVar(ImGuiStyleVar_LogSliderDeadZone, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 4);

		//Alignment
		ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));
		ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_Right;
		ImGui::GetStyle().ColorButtonPosition = ImGuiDir_Left;
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));

	}

	void Panels::EndColours()
	{
		//Colours
		//ImGui::PopStyleColor(26);

		//Main
		ImGui::PopStyleVar(8);

		//Borders
		ImGui::PopStyleVar(4);

		//Rounding
		ImGui::PopStyleVar(7);

		//Allignment
		ImGui::PopStyleVar(2);
		ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_Right;
		ImGui::GetStyle().ColorButtonPosition = ImGuiDir_Right;
	}

}