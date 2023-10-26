#pragma once

#include <Crystal/Crystal.hpp>
#include <Crystal/Examples/Camera2D.hpp>
#include <Crystal/Examples/Camera3D.hpp>

using namespace Crystal;

class GameLayer : public Layer
{
public:
	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Timestep& ts) override;
	void OnRender() override;
	void OnImGuiRender() override;

	void OnEvent(Event& e);

private:
	bool MousePressImGui(MouseButtonPressedEvent& e);
	bool WindowResize(WindowResizeEvent& e);

private:
	Ref<Camera3D> m_Camera3D;
	Ref<Camera2D> m_Camera2D;

	Ref<Texture2D> m_Tex;
	bool m_UseTex = false;
};