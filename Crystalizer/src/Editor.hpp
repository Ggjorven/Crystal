#pragma once

#include <Crystal/Crystal.hpp>

#include <filesystem>
#include <imgui.h>

//All editor layers
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

	void OnEvent(Event& e);

	static bool InWindow(ImVec2 windowPos, ImVec2 windowSize, MousePosition mousePosition);

private:
	std::filesystem::path m_Path = "test.crproj";

	Ref<Project> m_Project;
	Ref<FrameBuffer> m_FrameBuffer;

	Ref<Panels> m_Panels;
};