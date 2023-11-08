#include "Panels.hpp"

#include "Crystal/Core/Application.hpp"
#include "Crystal/Core/Events/Input/Input.hpp"
#include "Crystal/Utils/Utils.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_internal.h>

namespace Crystal
{

	void Panels::RunWindow(bool& running)
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
		
		Panels::BeginColours();
		ImGui::Begin("Run Buttons", (bool*)false, flags);

		float width = ImGui::GetCurrentWindow()->Size.x;
		glm::vec2 buttonSize = { 24.f, 24.f };

		ImGui::Dummy(ImVec2(width / 2.0f - buttonSize.x, 0.f));
		ImGui::SameLine();

		if (ImGui::ImageButton((ImTextureID)m_ButtonTex->GetRendererID(), ImVec2(buttonSize.x, buttonSize.y), { 0, 1 }, { 1, 0 }))
		{
			running = !running;
		}

		ImGui::End();
		Panels::EndColours();
	}
}