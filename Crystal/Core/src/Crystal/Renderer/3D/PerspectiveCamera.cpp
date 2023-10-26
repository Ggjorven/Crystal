#include "crpch.h"
#include "PerspectiveCamera.hpp"

namespace Crystal
{
	PerspectiveCamera::PerspectiveCamera(float width, float height)
		: m_AspectRatio(width / height),
		m_Properties(0.0f, 0.0f, 45.0f), m_Area(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f))
	{
	}

	PerspectiveCamera::~PerspectiveCamera()
	{
	}

	void PerspectiveCamera::OnUpdate(Timestep& ts)
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Area.Front, m_Area.Up);
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Properties.FOV), m_AspectRatio, 0.1f, 100.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewProjectionMatrix;
	}

	void PerspectiveCamera::OnEvent(Event& e)
	{
		EventHandler handler(e);

		handler.Handle<WindowResizeEvent>(CR_BIND_EVENT_FN(PerspectiveCamera::OnWindowResize));
	}

	void PerspectiveCamera::UpdateArea()
	{
		glm::vec3 newFront;

		newFront.x = cos(glm::radians(m_Properties.Yaw)) * cos(glm::radians(m_Properties.Pitch));
		newFront.y = sin(glm::radians(m_Properties.Pitch));
		newFront.z = sin(glm::radians(m_Properties.Yaw)) * cos(glm::radians(m_Properties.Pitch));

		m_Area.Front = glm::normalize(newFront);
		m_Area.Right = glm::normalize(glm::cross(m_Area.Front, m_Area.Up));
	}

	bool PerspectiveCamera::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		return false;
	}
}