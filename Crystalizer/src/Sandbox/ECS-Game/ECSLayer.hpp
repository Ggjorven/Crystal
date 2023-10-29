#pragma once

#include <Crystal/Crystal.hpp>
#include <Crystal/Examples/Camera2D.hpp>

using namespace Crystal;

class ECSLayer : public Layer
{
public:
	ECSLayer();
	virtual ~ECSLayer();

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Timestep& ts) override;
	void OnRender() override;
	void OnImGuiRender() override;

	void OnEvent(Event& e);

private:
	bool Reload(KeyPressedEvent& e);
	bool MousePress(MouseButtonPressedEvent& e);

private:
	Ref<Project> m_Project;
	Ref<Camera2D> m_Camera;
};