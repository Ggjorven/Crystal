#pragma once

#include <Crystal/Crystal.hpp>

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
	bool MousePress(MouseButtonPressedEvent& e);

private:
	Ref<Scene> m_Scene;

};