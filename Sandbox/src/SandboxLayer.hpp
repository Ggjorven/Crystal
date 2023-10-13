#pragma once

#include <Crystal/Crystal.hpp>
#include <Crystal/Examples/Camera2D.hpp>

class SandboxLayer : public Crystal::Layer
{
public:
	void OnAttach() override
	{
		m_Camera2D = new Crystal::Camera2D(
			(float)Crystal::Application::Get().GetWindow().GetWidth(),
			(float)Crystal::Application::Get().GetWindow().GetHeight(),
			true
		);

		m_Camera2D->SetMovementSpeed(500.0f);
		m_Camera2D->SetMaxZoomLevel(0.25f);
		
		Crystal::Renderer2D::SetOrigin({
			-((float)Crystal::Application::Get().GetWindow().GetWidth() / 2.0f),
			-((float)Crystal::Application::Get().GetWindow().GetHeight() / 2.0f)
		});

		float value = 360.0f;
		float radians = glm::radians<float>(value);
		float cosinus = glm::cos(radians);

		CR_WARN("Value: \t\t{0}", value);
		CR_WARN("Radians: \t\t{0}", radians);
		CR_WARN("Co-sinus: \t{0}", cosinus);
	}

	void OnDetach() override
	{
		delete m_Camera2D;
	}

	void OnUpdate(Crystal::Timestep& ts) override
	{
		m_Camera2D->OnUpdate(ts);
	}

	void OnRender() override
	{
		Crystal::Renderer2D::DrawQuad(glm::vec2(0.0f, 0.0f), glm::vec2(1280.0f, 720.0f), m_Camera2D->GetCamera(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	void OnImGuiRender() override
	{

	}

	void OnEvent(Crystal::Event& e)
	{
		m_Camera2D->OnEvent(e);
	}

private:
	Crystal::Camera2D* m_Camera2D;
};