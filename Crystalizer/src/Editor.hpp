#pragma once

#include <Crystal/Crystal.hpp>
#include <Crystal/Renderer/Tools/EditorCamera.hpp>

#include <filesystem>
#include <imgui.h>

#include "Panels/Panels.hpp"

// In seconds
#define CR_AUTOSAVE_INTERVAL 30.0f

using namespace Crystal;

class EditorLayer : public Layer
{
public:
	EditorLayer(const ApplicationInfo& appinfo);
	virtual ~EditorLayer();

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Timestep& ts) override;
	void OnRender() override;

	void OnImGuiRender() override;

	void OnEvent(Event& e) override;

	static bool InWindow(ImVec2 windowPos, ImVec2 windowSize, MousePosition mousePosition);

private:
	void CreateNewProject();
	void OpenProject(std::filesystem::path path);
	void SaveProject();

	void MenuBar();
	void ViewPort();

	bool KeyEvent(KeyPressedEvent& e);
	bool WindowClose(WindowCloseEvent& e);

private:
	std::filesystem::path m_Path = Utils::GetEnviromentVariable("CRYSTAL_DIR") + "\\Crystalizer\\Projects\\TestProj\\test.crproj";
	bool m_Running = false;

	Timestep m_AutoSaveTimer = 0.0f;

	Ref<Project> m_Project = nullptr;
	Ref<FrameBuffer> m_FrameBuffer = nullptr;

	Ref<Panels> m_Panels = nullptr;

	Ref<Texture2D> m_Texture = nullptr;
};