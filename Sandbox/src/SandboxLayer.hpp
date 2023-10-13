#pragma once

#include <Crystal/Crystal.hpp>

class SandboxLayer : public Crystal::Layer
{
public:
	void OnAttach() override
	{
		CR_INFO("LAYER");
	}

	void OnUpdate(Crystal::Timestep& ts) override
	{

	}

	void OnRender() override
	{
		Crystal::Renderer2D::DrawQuad(glm::vec2(100.0f, 100.0f), glm::vec2(100.0f, 100.0f), nullptr, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	void OnImGuiRender() override
	{

	}

private:

};