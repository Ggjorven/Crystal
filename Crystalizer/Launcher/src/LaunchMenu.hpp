#pragma once

#include <Crystal/Crystal.hpp>

using namespace Crystal;

class LaunchMenu : public Layer
{
public:
	LaunchMenu() = default;
	virtual ~LaunchMenu() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Timestep& ts) override;
	void OnRender() override;
	void OnImGuiRender() override;

	void OnEvent(Event& e);

private:
	void BeginColours();
	void EndColours();

private:
	Ref<Project> m_Project;

	Ref<Texture2D> m_CrystalEngineTex;
	Ref<Texture2D> m_NewTex;
	Ref<Texture2D> m_OpenTex;

	MousePosition m_LastMousePosition;

};