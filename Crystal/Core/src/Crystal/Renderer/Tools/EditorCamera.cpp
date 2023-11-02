#include "crpch.h"
#include "EditorCamera.hpp"

#include "Crystal/Core/Application.hpp"

#include "Crystal/Core/Events/Codes/MouseCodes.hpp"

namespace Crystal
{

	EditorCamera::EditorCamera()
	{
		Window& window = Application::Get().GetWindow();

		m_Camera = CreateRef<OrthoGraphicCamera>((float)window.GetViewportWidth() / 2.0f * -1, (float)window.GetViewportWidth() / 2.0f, 
			(float)window.GetViewportHeight() / 2.0f * -1, (float)window.GetViewportHeight() / 2.0f);
	}

	EditorCamera::~EditorCamera()
	{
	}

	void EditorCamera::OnUpdate(Timestep& ts)
	{
		Window& window = Application::Get().GetWindow();

		m_Camera->SetProjection((float)window.GetViewportWidth() / 2.0f * -1, (float)window.GetViewportWidth() / 2.0f,
			(float)window.GetViewportHeight() / 2.0f * -1, (float)window.GetViewportHeight() / 2.0f
		);

		if (Input::IsKeyPressed(m_MovementKey) && Input::IsMousePressed(CR_MOUSE_BUTTON_LEFT))
		{
			MousePosition mousePosition = Input::GetMousePosition();

			float xOffset = static_cast<float>(mousePosition.X - m_LastMousePosition.X);
			float yOffset = static_cast<float>(m_LastMousePosition.Y - mousePosition.Y);

			//Update position
			m_Camera->SetPosition({ m_Camera->GetPosition().x + xOffset, m_Camera->GetPosition().y + yOffset, m_Camera->GetPosition().z });
			m_Position = { m_Camera->GetPosition().x, m_Camera->GetPosition().y };
		}

		m_LastMousePosition = Input::GetMousePosition();
	}

	void EditorCamera::OnEvent(Event& e)
	{
	}

}