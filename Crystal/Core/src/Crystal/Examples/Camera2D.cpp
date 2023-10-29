#include "crpch.h"
#include "Camera2D.hpp"

#include "Crystal/Core/Application.hpp"

#include "Crystal/Core/Events/Input/Input.hpp"
#include "Crystal/Core/Events/Codes/KeyCodes.hpp"

namespace Crystal
{
	Camera2D::Camera2D(float width, float height, bool rotation)
		: m_Width(width), m_Height(height), m_Rotation(rotation)
	{
		m_Camera = CreateRef<OrthoGraphicCamera>(-width / 2.0f * m_ZoomLevel, width / 2.0f * m_ZoomLevel, -height / 2.0f * m_ZoomLevel, height / 2.0f * m_ZoomLevel);
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::OnUpdate(Timestep& ts)
	{
		if (Input::IsKeyPressed(CR_KEY_LEFT))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
		}
		else if (Input::IsKeyPressed(CR_KEY_RIGHT))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
		}

		if (Input::IsKeyPressed(CR_KEY_UP))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
		}
		else if (Input::IsKeyPressed(CR_KEY_DOWN))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_MovementSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(CR_KEY_KP_4))
				m_CameraRotation -= m_RotationSpeed * ts;

			if (Input::IsKeyPressed(CR_KEY_KP_6))
				m_CameraRotation += m_RotationSpeed * ts;



			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera->SetRotation(m_CameraRotation);
		}

		m_Camera->SetPosition({ m_CameraPosition.x - m_Origin.x, m_CameraPosition.y - m_Origin.y, m_CameraPosition.z });
	}

	void Camera2D::OnEvent(Event& e)
	{
		EventHandler dispatcher(e);

		dispatcher.Handle<MouseScrolledEvent>(CR_BIND_EVENT_FN(Camera2D::OnMouseScrolled));
		dispatcher.Handle<WindowResizeEvent>(CR_BIND_EVENT_FN(Camera2D::OnWindowResized));
	}

	bool Camera2D::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, m_MaxZoomLevel);

		float width = static_cast<float>(Application::Get().GetWindow().GetViewportWidth()) / 2.0f;
		float height = static_cast<float>(Application::Get().GetWindow().GetViewportHeight()) / 2.0f;

		m_Camera->SetProjection(-width * m_ZoomLevel, width * m_ZoomLevel, -height * m_ZoomLevel, height * m_ZoomLevel);

		return false;
	}

	bool Camera2D::OnWindowResized(WindowResizeEvent& e)
	{
		float width = static_cast<float>(e.GetWidth()) / 2.0f;
		float height = static_cast<float>(e.GetHeight()) / 2.0f;

		m_Camera->SetProjection(-width * m_ZoomLevel, width * m_ZoomLevel, -height * m_ZoomLevel, height * m_ZoomLevel);
		//m_CameraPosition = { m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z };

		return false;
	}

	void Camera2D::UpdateView()
	{
		m_Camera->SetPosition({ m_CameraPosition.x - m_Origin.x, m_CameraPosition.y - m_Origin.y, m_CameraPosition.z });
	}
}