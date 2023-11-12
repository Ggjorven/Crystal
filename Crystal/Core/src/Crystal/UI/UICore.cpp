#include "crpch.h"
#include "UICore.hpp"

#include <imgui.h>
#include <imgui_internal.h>

namespace Crystal::UI
{

	bool BeginECSComponent(const char* label, Ref<Texture2D> icon)
	{
		bool open = false;

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.0f, 4.0f));
		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;

		if (ImGui::TreeNodeEx(label, treeNodeFlags))
		{
			open = true;
			ImGui::TreePop();
		}

		if (icon)
		{
			ImVec2 cursorPos = ImGui::GetCursorPos();
			ImVec2 iconSize(16, 16);

			ImGui::SetCursorPos(ImVec2(cursorPos.x, cursorPos.y - (ImGui::GetStyle().FramePadding.y * 5.63)));
			ImGui::Image((ImTextureID)icon->GetRendererID(), iconSize, { 0, 1 }, { 1, 0 });

			ImGui::SetCursorPos(ImVec2(cursorPos.x, cursorPos.y));
		}


		ImGui::PopStyleVar(1);
		return open;
	}

	void Vector3(const char* label, Vec3<float>& value, const Vec4<float>& colourX, const Vec4<float>& colourY, const Vec4<float>& colourZ)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.0f, 4.f));

		float dragSpeed = 1.0f;

		float buttonSize = 21.0f;
		float draggerSize = 50.0f;
		float spacingBase = 3.0f;
		float extra = 12.0f;

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(colourX.x - 0.30f, colourX.y + 0.18f, colourX.z + 0.18f, colourX.w));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(colourX.x, colourX.y, colourX.z, colourX.w));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(colourX.x - 0.31f, colourX.y, colourX.z, colourX.w));

		if (ImGui::Button((std::string("X##X") + std::string(label)).c_str(), ImVec2(buttonSize, buttonSize)))
			value.X = 0.0f;

		ImGui::SameLine(spacingBase + buttonSize + extra, -1.0f);
		ImGui::SetNextItemWidth(draggerSize);
		ImGui::DragFloat((std::string("##X") + std::string(label)).c_str(), &value.x, dragSpeed, 0.0f, 0.0f, "%.1f", ImGuiSliderFlags_None);

		ImGui::PopStyleColor(3);
		ImGui::SameLine(spacingBase * 2 + buttonSize + draggerSize + extra, -1.0f);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(colourY.x + 0.18f, colourY.y - 0.30f, colourY.z + 0.18f, colourY.w));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(colourY.x, colourY.y, colourY.z, colourY.w));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(colourY.x, colourY.y - 0.31f, colourY.z, colourY.w));

		if (ImGui::Button((std::string("Y##Y") + std::string(label)).c_str(), ImVec2(buttonSize, buttonSize)))
			value.Y = 0.0f;

		ImGui::SameLine(spacingBase * 3 + buttonSize + draggerSize + buttonSize + extra, -1.0f);
		ImGui::SetNextItemWidth(draggerSize);
		ImGui::DragFloat((std::string("##Y") + std::string(label)).c_str(), &value.y, dragSpeed, 0.0f, 0.0f, "%.1f", ImGuiSliderFlags_None);

		ImGui::PopStyleColor(3);
		ImGui::SameLine(spacingBase * 4 + buttonSize + draggerSize + buttonSize + draggerSize + extra, -1.0f);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(colourZ.x + 0.18f, colourZ.y + 0.18f, colourZ.z - 0.30f, colourZ.w));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(colourZ.x, colourZ.y, colourZ.z, colourZ.w));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(colourZ.x, colourZ.y, colourZ.z - 0.31f, colourZ.w));

		if (ImGui::Button((std::string("Z##") + std::string(label)).c_str(), ImVec2(buttonSize, buttonSize)))
			value.Z = 0.0f;

		ImGui::SameLine(spacingBase * 5 + buttonSize + draggerSize + buttonSize + draggerSize + buttonSize + extra, -1.0f);
		ImGui::SetNextItemWidth(draggerSize);
		ImGui::DragFloat((std::string("##Z") + std::string(label)).c_str(), &value.z, dragSpeed, 0.0f, 0.0f, "%.1f", ImGuiSliderFlags_None);

		ImGui::SameLine();
		ImGui::Text((std::string("<- ") + std::string(label)).c_str());

		ImGui::PopStyleColor(3);

		ImGui::PopStyleVar(2);
	}

}