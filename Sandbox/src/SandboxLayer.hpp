#pragma once

#include <Crystal/Crystal.hpp>
#include <Crystal/Examples/Camera2D.hpp>

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		
		m_CameraOrigin = {
			-((float)Crystal::Application::Get().GetWindow().GetWidth() / 2.0f),
			(float)Crystal::Application::Get().GetWindow().GetHeight() / 2.0f
		};
		m_Camera2D->SetOrigin(m_CameraOrigin);

		m_Position = { 0.0f, 0.0f };
		m_Size = { 100.0f, 100.0f };
		m_Origin = { -(m_Size.x / 2.0f), m_Size.y / 2.0f };

		m_Texture = Crystal::Texture2D::Create("assets/textures/test.png");

		/*
		float value = 360.0f;
		float radians = glm::radians<float>(value);
		float cosinus = glm::cos(radians);

		CR_WARN("Value: \t\t{0}", value);
		CR_WARN("Radians: \t\t{0}", radians);
		CR_WARN("Co-sinus: \t{0}", cosinus);
		*/
	}

	void OnDetach() override
	{
		delete m_Camera2D;
	}

	void OnUpdate(Crystal::Timestep& ts) override
	{
		m_Camera2D->OnUpdate(ts);

		m_Camera2D->SetOrigin(m_CameraOrigin);

		m_Origin = { -(m_Size.x / 2.0f), m_Size.y / 2.0f };
		Crystal::Renderer2D::SetQuadOrigin(m_Origin);
	}

	void OnRender() override
	{
		Crystal::Renderer2D::DrawQuad(m_Position, m_Size, m_Texture, m_Camera2D->GetCamera());
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		
		//ImGui::DragFloat2("camera origin", glm::value_ptr(m_CameraOrigin), 0.5f);

		//ImGui::DragFloat2("origin", glm::value_ptr(m_Origin), 0.5f);
		ImGui::DragFloat2("position", glm::value_ptr(m_Position), 0.5f);
		ImGui::DragFloat2("size", glm::value_ptr(m_Size), 0.5f);

		ImGui::End();
	}

	void OnEvent(Crystal::Event& e)
	{
		m_Camera2D->OnEvent(e);
	}

private:
	Crystal::Camera2D* m_Camera2D;
	glm::vec2 m_CameraOrigin;

	glm::vec2 m_Position;
	glm::vec2 m_Size;
	glm::vec2 m_Origin;

	Crystal::Ref<Crystal::Texture2D> m_Texture;
};