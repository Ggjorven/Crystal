#pragma once

#include <Crystal/Crystal.hpp>
#include <Crystal/Renderer/Tools/EditorCamera.hpp>

#include <filesystem>
#include <imgui.h>

#include "Panels/Panels.hpp"

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
	void SaveProject();

	void MenuBar();
	void ViewPort();

	bool KeyEvent(KeyPressedEvent& e);

private:
	std::filesystem::path m_Path = Utils::GetEnviromentVariable("CRYSTAL_DIR") + "\\Crystalizer\\Projects\\TestProj\\test.crproj";
	bool m_Running = false;

	Ref<Project> m_Project = nullptr;
	Ref<FrameBuffer> m_FrameBuffer = nullptr;

	Ref<Panels> m_Panels = nullptr;
};