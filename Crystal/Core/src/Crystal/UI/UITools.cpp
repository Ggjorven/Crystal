#include "crpch.h"
#include "UITools.hpp"

#include <imgui.h>
#include <imgui_internal.h>

namespace Crystal::UI::Tools
{

    static bool s_Firstrun = true;
    static float s_DefaultFontSize;

	void SetContextFontSize(float fontSize)
	{
        ImGuiIO& io = ImGui::GetIO();
        ImFont* font = io.Fonts->Fonts[0]; // Assuming you are using the first font, change as needed

        if (s_Firstrun)
        {
            ImGuiWindow* window = ImGui::GetCurrentWindow();
            s_DefaultFontSize = window->FontWindowScale;

            s_Firstrun = false;
        }

        if (fontSize == 0.0f)
        {
            ImGui::SetWindowFontScale(s_DefaultFontSize);
            return;
        }

        ImGui::SetWindowFontScale(fontSize);
	}

}