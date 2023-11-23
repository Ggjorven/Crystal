#include "LaunchMenu.hpp"

#include <fstream>
#include <filesystem>

#include <imgui.h>
#include <imgui_internal.h>

#include <shellapi.h> // TODO(Jorben): Make not windows dependant

void LaunchMenu::OnAttach()
{
	
	const char* settings = R"(
[Window][DockSpaceViewport_11111111]
Pos=0,0
Size=500,350
Collapsed=0

[Window][Debug##Default]
ViewportPos=770,425
ViewportId=0x9F5F46A1
Size=400,400
Collapsed=0

[Window][Viewport]
Pos=333,19
Size=947,701
Collapsed=0
DockId=0x00000002,0

[Window][Objects]
Pos=0,19
Size=331,372
Collapsed=0
DockId=0x00000003,0

[Window][Properties]
Pos=0,393
Size=331,327
Collapsed=0
DockId=0x00000004,0

[Window][##Launcher]
Pos=0,0
Size=500,350
Collapsed=0
DockId=0x00000002

[Docking][Data]
DockSpace     ID=0x8B93E3BD Window=0xA787BDB4 Pos=710,365 Size=500,350 Split=X
  DockNode    ID=0x00000001 Parent=0x8B93E3BD SizeRef=331,701 Split=Y Selected=0x967E7699
    DockNode  ID=0x00000003 Parent=0x00000001 SizeRef=223,372 Selected=0x967E7699
    DockNode  ID=0x00000004 Parent=0x00000001 SizeRef=223,327 HiddenTabBar=1 Selected=0x199AB496
  DockNode    ID=0x00000002 Parent=0x8B93E3BD SizeRef=947,701 CentralNode=1 Selected=0x1B54E6E9
	)";

	ImGuiIO& io = ImGui::GetIO();
	io.WantSaveIniSettings = true;

	ImGui::ClearIniSettings();
	ImGui::LoadIniSettingsFromMemory(settings, std::strlen(settings));

	settings = ImGui::SaveIniSettingsToMemory();
	io.WantSaveIniSettings = false;

	UI::Init();
	
	m_CrystalEngineTex = Texture2D::Create(Utils::GetEnviromentVariable("CRYSTAL_DIR") + "\\Crystalizer\\assets\\textures\\Crystal-Engine.png");
	m_NewTex = Texture2D::Create(Utils::GetEnviromentVariable("CRYSTAL_DIR") + "\\Crystalizer\\assets\\textures\\New.png");
	//m_OpenTex = Texture2D::Create(Utils::GetEnviromentVariable("CRYSTAL_DIR") + "\\Crystalizer\\assets\\textures\\Open.png");
}

void LaunchMenu::OnDetach()
{
}

void LaunchMenu::OnUpdate(Timestep& ts)
{
	// TODO(Jorben): Add a better way of moving the window
	const Window& window = Application::Get().GetWindow();

	if (Input::IsMousePressed(CR_MOUSE_BUTTON_LEFT))
	{
		MousePosition mousePosition = Input::GetMousePosition();

		auto xOffset = static_cast<float>(mousePosition.X - m_LastMousePosition.X);
		auto yOffset = static_cast<float>(m_LastMousePosition.Y - mousePosition.Y);

		//Update position
		window.SetWindowPosition(Vec2<int>(window.GetWindowPosition().x + xOffset * 2.f, window.GetWindowPosition().y - yOffset * 2.f));
	}

	m_LastMousePosition = Input::GetMousePosition();
}

void LaunchMenu::OnRender()
{
}

void LaunchMenu::OnImGuiRender()
{
	BeginColours();
	ImGui::DockSpaceOverViewport((const ImGuiViewport*)0, ImGuiDockNodeFlags_NoTabBar);

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar;
	ImGui::Begin("##Launcher", (bool*)false, flags);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);

	const Window& window = Application::Get().GetWindow();
	
	//Menubar
	//ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::Text("Crystal Options Menu");

		float size = 16.f;
		ImGui::SetCursorPos(ImVec2(window.GetWidth() / 2.6f - size, 0.0f));
		ImGui::SetNextItemWidth(size);
		if (ImGui::MenuItem("X"))
		{
			WindowCloseEvent e;
			Application::Get().DispatchEvent<WindowCloseEvent>(e);
		}

		ImGui::EndMainMenuBar();
	}
	//ImGui::PopStyleColor(1);

	ImVec2 buttonSize = { 150.0f, 150.0f };


	ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
	ImGui::Image(reinterpret_cast<ImTextureID>(m_CrystalEngineTex->GetRendererID()), ImVec2((float)window.GetWidth() / 2.5f, (float)window.GetHeight() / 2.5f), { 0, 1 }, { 1, 0 });

	ImGui::SetCursorPos(ImVec2(window.GetWidth() / 6.0f - buttonSize.x / 1.4f - 35, window.GetHeight() / 6.0f - 15 + 25));
	if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(m_NewTex->GetRendererID()), buttonSize, { 0, 1 }, { 1, 0 }))
	{
		std::string path = Utils::SaveFile(".crproj\0*.crproj\0All Files\0*.*\0");
		if (!path.empty())
		{
			std::filesystem::path filePath = std::filesystem::path(Utils::SaveFile(".crproj\0*.crproj\0All Files\0*.*\0"));

			std::ofstream outFile(filePath);
			outFile << " " << std::endl;

#ifndef CR_DIST
			ShellExecuteA(NULL, "open", std::string(Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Dist-windows-x86_64\\Crystalizer\\Crystalizer.exe")).c_str(), filePath.string().c_str(), NULL, SW_SHOWDEFAULT);
#else // TODO(Jorben): Replace with bottom line on distribution
			ShellExecuteA(NULL, "open", std::string(Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Dist-windows-x86_64\\Crystalizer\\Crystalizer.exe")).c_str(), filePath.string().c_str(), NULL, SW_SHOWDEFAULT);
			//ShellExecuteA(NULL, "open", std::string(Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Crystalizer\\Crystalizer.exe")).c_str(), filePath.c_str(), NULL, SW_SHOWDEFAULT);
#endif
			WindowCloseEvent e;
			Application::Get().DispatchEvent<WindowCloseEvent>(e);
		}
	}

	ImGui::SetCursorPos(ImVec2(window.GetWidth() / 6.0f + buttonSize.x / 1.4f - 35, window.GetHeight() / 6.0f - 15 + 25));
	if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(m_CrystalEngineTex->GetRendererID()), buttonSize, { 0, 1 }, { 1, 0 })) // TODO(Jorben): Replace New Tex with open tex
	{
		std::string file = Utils::OpenFile(".crproj\0*.crproj\0All Files\0*.*\0");
		if (!file.empty())
		{
#ifndef CR_DIST
			ShellExecuteA(NULL, "open", std::string(Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Dist-windows-x86_64\\Crystalizer\\Crystalizer.exe")).c_str(), file.c_str(), NULL, SW_SHOWDEFAULT);
#else // TODO(Jorben): Replace with bottom line on distribution
			ShellExecuteA(NULL, "open", std::string(Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Dist-windows-x86_64\\Crystalizer\\Crystalizer.exe")).c_str(), file.c_str(), NULL, SW_SHOWDEFAULT);
			//ShellExecuteA(NULL, "open", std::string(Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Crystalizer\\Crystalizer.exe")).c_str(), file.c_str(), NULL, SW_SHOWDEFAULT);
#endif
			WindowCloseEvent e;
			Application::Get().DispatchEvent<WindowCloseEvent>(e);
		}
	}
	ImGui::PopStyleVar(1);

	/*
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 7.f);
	ImVec2 xButtonSize = { 22.f, 22.f };
	ImGui::SetCursorPos(ImVec2(window.GetWidth() / 2.65f - xButtonSize.x / 2.0f, 0.0f));

	if (ImGui::Button("x", xButtonSize))
	{
		WindowCloseEvent e;
		Application::Get().DispatchEvent<WindowCloseEvent>(e);
	}

	ImGui::PopStyleVar(1);
	*/

	ImGui::End();
	EndColours();
}

void LaunchMenu::OnEvent(Event& e)
{
}

void LaunchMenu::BeginColours()
{
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
	colours[ImGuiCol_Tab] = ImVec4(0.09f, 0.25f, 0.28f, 0.0f);
	colours[ImGuiCol_TabHovered] = ImVec4(0.20f, 0.63f, 0.72f, 0.0f);
	colours[ImGuiCol_TabActive] = ImVec4(0.13f, 0.40f, 0.46f, 0.0f);
	colours[ImGuiCol_TabUnfocused] = ImVec4(0.03f, 0.11f, 0.12f, 0.0f);
	colours[ImGuiCol_TabUnfocusedActive] = ImVec4(0.34f, 0.88f, 1.00f, 0.0f);
	colours[ImGuiCol_DockingPreview] = ImVec4(0.20f, 0.63f, 0.72f, 0.0f);
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

void LaunchMenu::EndColours()
{
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
