#include "crpch.h"
#include "EditorCamera.hpp"

#include "Crystal/Core/Application.hpp"

#include "Crystal/Core/Events/Codes/MouseCodes.hpp"

namespace Crystal
{

	EditorCamera::EditorCamera()
	{
		const Window& window = Application::Get().GetWindow();

		m_Camera = CreateRef<OrthoGraphicCamera>((float)window.GetViewportWidth() / 2.0f * -1, (float)window.GetViewportWidth() / 2.0f, 
			(float)window.GetViewportHeight() / 2.0f * -1, (float)window.GetViewportHeight() / 2.0f);
	}

	EditorCamera::~EditorCamera()
	{
	}

	void EditorCamera::OnUpdate(Timestep& ts)
	{
		const Window& window = Application::Get().GetWindow();

		m_Camera->SetProjection((float)window.GetViewportWidth() / 2.0f * -1 * m_Zoom, (float)window.GetViewportWidth() / 2.0f * m_Zoom,
			(float)window.GetViewportHeight() / 2.0f * -1 * m_Zoom, (float)window.GetViewportHeight() / 2.0f * m_Zoom
		);

		if (Input::IsKeyPressed(m_MovementKey) && Input::IsKeyPressed(CR_KEY_LEFT_CONTROL))
		{
			m_LastMousePosition = Input::GetMousePosition();

			//Update position
			m_Camera->SetPosition({ m_DefaultPosition.x, m_DefaultPosition.y, m_Camera->GetPosition().z });
			m_Position = { m_Camera->GetPosition().x, m_Camera->GetPosition().y };

			return;
		}

		if (Input::IsKeyPressed(m_MovementKey) && Input::IsMousePressed(CR_MOUSE_BUTTON_LEFT))
		{

			MousePosition mousePosition = Input::GetMousePosition();

			auto xOffset = static_cast<float>(mousePosition.X - m_LastMousePosition.X);
			auto yOffset = static_cast<float>(m_LastMousePosition.Y - mousePosition.Y);

			//Update position
			m_Camera->SetPosition({ m_Camera->GetPosition().x - xOffset, m_Camera->GetPosition().y - yOffset, m_Camera->GetPosition().z });
			m_Position = { m_Camera->GetPosition().x, m_Camera->GetPosition().y };
		}

		m_LastMousePosition = Input::GetMousePosition();
	}

	void EditorCamera::OnEvent(Event& e)
	{
		EventHandler handler(e);

		handler.Handle<MouseScrolledEvent>(CR_BIND_EVENT_FN(EditorCamera::MouseScrolled));
	}

	bool EditorCamera::MousePress(MouseButtonPressedEvent& e)
	{
		return false;
	}

	bool EditorCamera::MouseScrolled(MouseScrolledEvent& e)
	{
		m_Zoom -= e.GetYOffset() * 0.25f;
		m_Zoom = std::max(m_Zoom, 0.25f);

		return false;
	}

}