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
		m_Origin = { m_Size.x / 2.0f, -(m_Size.y / 2.0f) };
		//m_Origin = { 0.0f, 0.0f };

		m_Texture = Crystal::Texture2D::Create("assets/textures/Mario.png");
		m_TexCoords = Crystal::TexCoords(0, 0, m_Texture->GetWidth(), m_Texture->GetHeight());

		Crystal::RendererCommand::SetClearColour(glm::vec4(0.1f, 0.2f, 0.2f, 1.0f));
	}

	void OnDetach() override
	{
		delete m_Camera2D;
	}

	void OnUpdate(Crystal::Timestep& ts) override
	{
		m_Camera2D->OnUpdate(ts);
		m_Camera2D->SetOrigin(m_CameraOrigin);

		m_Origin = { m_Size.x / 2.0f, -(m_Size.y / 2.0f) };
		//Crystal::Renderer2D::SetQuadOrigin(m_Origin);
	}

	void OnRender() override
	{
		//Crystal::Renderer2D::DrawQuad(m_Position, m_Size, m_Texture, m_Camera2D->GetCamera());
		Crystal::Renderer2D::DrawQuad(m_Position, m_Size, m_Origin, m_Texture, m_TexCoords, m_Camera2D->GetCamera());
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		
		//ImGui::DragFloat2("camera origin", glm::value_ptr(m_CameraOrigin), 0.5f);

		//Texture coords
		ImGui::DragInt("Tex: X", (int*) &m_TexCoords.X, 0.5f);
		ImGui::DragInt("Tex: Y", (int*) &m_TexCoords.Y, 0.5f);
		ImGui::DragInt("Tex: Width", (int*) &m_TexCoords.Width, 0.5f);
		ImGui::DragInt("Tex: Height", (int*) &m_TexCoords.Height, 0.5f);

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
	Crystal::TexCoords m_TexCoords;
};