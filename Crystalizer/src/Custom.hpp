#pragma once

#include <Crystal/Crystal.hpp>

#include <filesystem>

using namespace Crystal;

class CustomLayer : public Layer
{
public:
	CustomLayer(const ApplicationInfo& appinfo);
	virtual ~CustomLayer();

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Timestep& ts) override;
	void OnRender() override;

	void OnImGuiRender() override;

	void OnEvent(Event& e) override;

private:

};