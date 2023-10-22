#pragma once

#include <Crystal/Crystal.hpp>

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

};