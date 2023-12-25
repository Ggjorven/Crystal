#include "crpch.h"
#include "EditorCamera.hpp"

#include "Crystal/Core/Application.hpp"

#include "Crystal/Core/Events/Codes/MouseCodes.hpp"

namespace Crystal
{

	EditorCamera2D::EditorCamera2D()
	{
		const Window& window = Application::Get().GetWindow();

		m_Camera = CreateRef<OrthoGraphicCamera>((float)window.GetViewportWidth() / 2.0f * -1, (float)window.GetViewportWidth() / 2.0f, 
			(float)window.GetViewportHeight() / 2.0f * -1, (float)window.GetViewportHeight() / 2.0f);
	}

	EditorCamera2D::~EditorCamera2D()
	{
	}

	void EditorCamera2D::OnUpdate(Timestep& ts)
	{
		const Window& window = Application::Get().GetWindow();

		m_Camera->SetProjection((float)window.GetViewportWidth() / 2.0f * -1 * m_Zoom, (float)window.GetViewportWidth() / 2.0f * m_Zoom,
			(float)window.GetViewportHeight() / 2.0f * -1 * m_Zoom, (float)window.GetViewportHeight() / 2.0f * m_Zoom
		);

		if (Input::IsKeyPressed(m_MovementKey) && Input::IsKeyPressed(CR_KEY_LEFT_CONTROL))
		{
			m_LastMousePosition = Input::GetMousePosition();

			//Update position
			m_Zoom = 1.0f;
			m_Position = { m_DefaultPosition.x, m_DefaultPosition.y };
			m_Camera->SetPosition({ m_Position.x, m_Position.y, m_Camera->GetPosition().z });
		}

		if (Input::IsKeyPressed(m_MovementKey) && Input::IsMousePressed(CR_MOUSE_BUTTON_LEFT))
		{
			MousePosition mousePosition = Input::GetMousePosition();

			auto xOffset = static_cast<float>(mousePosition.X - m_LastMousePosition.X);
			auto yOffset = static_cast<float>(m_LastMousePosition.Y - mousePosition.Y);

			//Update position
			m_Position = { m_Position.x - xOffset * m_Zoom, m_Position.y - yOffset * m_Zoom };
			m_Camera->SetPosition({ m_Position.x, m_Position.y, m_Camera->GetPosition().z });
		}
		m_Camera->SetPosition(Vec3<float>(m_Position.x + (float)window.GetViewportWidth() / 2.0f, m_Position.y + (float)window.GetViewportHeight() / 2.0f, m_Camera->GetPosition().z));
		m_LastMousePosition = Input::GetMousePosition();
	}

	void EditorCamera2D::OnEvent(Event& e)
	{
		EventHandler handler(e);

		handler.Handle<MouseScrolledEvent>(CR_BIND_EVENT_FN(EditorCamera2D::MouseScrolled));
	}

	bool EditorCamera2D::MousePress(MouseButtonPressedEvent& e)
	{
		return false;
	}

	bool EditorCamera2D::MouseScrolled(MouseScrolledEvent& e)
	{
		m_Zoom -= e.GetYOffset() * 0.25f;
		m_Zoom = std::max(m_Zoom, 0.25f);

		return false;
	}



    EditorCamera3D::EditorCamera3D()
        : m_LastMousePosition(MousePosition(0.0f, 0.0f)),
        m_MovementSpeed(2.5f), m_MouseSensitivity(0.1f)
    {
		const Window& window = Application::Get().GetWindow();
        m_Camera = CreateRef<PerspectiveCamera>((float)window.GetViewportWidth(), (float)window.GetViewportHeight());
        m_Camera->UpdateArea();

        Input::SetCursorMode(CR_CURSOR_DISABLED);
    }

    EditorCamera3D::~EditorCamera3D()
    {
    }

    void EditorCamera3D::OnUpdate(Timestep& ts)
    {
        const Window& window = Application::Get().GetWindow();

        m_Camera->OnUpdate(ts);
        m_Camera->SetProjectionMatrix(glm::perspective(glm::radians(m_Camera->GetSettings().FOV), (float)window.GetViewportWidth() / (float)window.GetViewportHeight(), 0.1f, 100.0f));

        if (Input::IsKeyPressed(CR_KEY_LEFT_ALT))
        {
            float velocity = m_MovementSpeed * ts;
            Vec3<float> moveDirection = { 0.0f, 0.0f, 0.0f };

            MovementArea& area = m_Camera->GetArea();

            // Calculate forward/backward and left/right movement.
            if (Input::IsKeyPressed(CR_KEY_W))
                moveDirection += area.Front;
            if (Input::IsKeyPressed(CR_KEY_S))
                moveDirection -= area.Front;
            if (Input::IsKeyPressed(CR_KEY_A))
                moveDirection -= area.Right;
            if (Input::IsKeyPressed(CR_KEY_D))
                moveDirection += area.Right;

            // Calculate up/down movement.
            /*
            if (Input::IsKeyPressed(CR_KEY_SPACE))
                moveDirection += area.Up;
            */
            if (Input::IsKeyPressed(CR_KEY_LEFT_SHIFT))
                moveDirection -= area.Up;

            if (glm::length(Convert(moveDirection)) > 0.0f)
                moveDirection = glm::normalize(Convert(moveDirection));

            // Update the camera position.
            m_Camera->GetPosition() += Convert(moveDirection) * velocity;

            if (m_FirstUpdate)
            {
				m_LastMousePosition = Input::GetMousePosition();
				m_FirstUpdate = false;
            }

            //Mouse movement
            MousePosition mousePosition = Input::GetMousePosition();

            float xOffset = static_cast<float>(mousePosition.X - m_LastMousePosition.X);
            float yOffset = static_cast<float>(m_LastMousePosition.Y - mousePosition.Y);

            //Reset cursor
            Window& window = Application::Get().GetWindow();
            int width = window.GetViewportWidth();
            int height = window.GetViewportHeight();

            Input::SetCursorPosition({ width / 2.0f + (float)window.GetViewportX(), height / 2.0f + (float)window.GetViewportY() });

            m_LastMousePosition.X = static_cast<float>(width / 2.f) + (float)window.GetViewportX();
            m_LastMousePosition.Y = static_cast<float>(height / 2.f) + (float)window.GetViewportY();

            xOffset *= m_MouseSensitivity;
            yOffset *= m_MouseSensitivity;

            //Set new settings
            CameraSettings& settings = m_Camera->GetSettings();

            settings.Yaw += xOffset;
            settings.Pitch += yOffset;

            // Cap movement
            if (settings.Pitch > 89.0f)
                settings.Pitch = 89.0f;
            if (settings.Pitch < -89.0f)
                settings.Pitch = -89.0f;

            m_Camera->UpdateArea();

			Input::SetCursorMode(CR_CURSOR_DISABLED);
        }
        else
        {
			Input::SetCursorMode(CR_CURSOR_SHOWN);
            m_FirstUpdate = true;
        }
    }

    void EditorCamera3D::OnEvent(Event& e)
    {
        EventHandler handler(e);

        handler.Handle<KeyPressedEvent>(CR_BIND_EVENT_FN(EditorCamera3D::KeyEvent));
        handler.Handle<MouseButtonPressedEvent>(CR_BIND_EVENT_FN(EditorCamera3D::MousePressedEvent));

        m_Camera->OnEvent(e);
    }

    bool EditorCamera3D::MousePressedEvent(MouseButtonPressedEvent& e)
    {

        return false;
    }

    bool EditorCamera3D::KeyEvent(KeyPressedEvent& e)
    {

        return false;
    }

}