#include "crpch.h"
#include "Camera3D.hpp"

#include "Crystal/Core/Application.hpp"

#include "Crystal/Core/Events/Codes/KeyCodes.hpp"
#include "Crystal/Core/Events/Codes/MouseCodes.hpp"

namespace Crystal
{

	Camera3D::Camera3D(float width, float height)
		: m_Camera(CreateRef<PerspectiveCamera>(width, height)),
		m_Escaped(false), m_FirstMouseCheck(true),
		m_LastMousePosition(MousePosition(0.0f, 0.0f)),
		m_MovementSpeed(2.5f), m_MouseSensitivity(0.1f)
	{
        m_Camera->UpdateArea();

        Input::SetCursorMode(CR_CURSOR_DISABLED);
	}

	Camera3D::~Camera3D()
	{
	}

	void Camera3D::OnUpdate(Timestep& ts)
	{
        m_Camera->UpdateMatrices();

        //Key presses
        if (!m_Escaped)
        {
            float velocity = m_MovementSpeed * ts;
            Vec3<float> moveDirection = { 0.0f, 0.0f, 0.0f };

            MovementArea& area = m_Camera->GetArea();

            // Calculate forward/backward and left/right movement.
            if (Input::IsKeyPressed(CR_KEY_W))
                moveDirection += Vec3<float>(area.Front.x, 0.0f, area.Front.z);
            if (Input::IsKeyPressed(CR_KEY_S))
                moveDirection -= Vec3<float>(area.Front.x, 0.0f, area.Front.z);
            if (Input::IsKeyPressed(CR_KEY_A))
                moveDirection -= area.Right;
            if (Input::IsKeyPressed(CR_KEY_D))
                moveDirection += area.Right;

            // Calculate up/down movement.
            if (Input::IsKeyPressed(CR_KEY_SPACE))
                moveDirection += area.Up;
            if (Input::IsKeyPressed(CR_KEY_LEFT_SHIFT))
                moveDirection -= area.Up;

            if (glm::length(Convert(moveDirection)) > 0.0f)
                moveDirection = glm::normalize(Convert(moveDirection));

            // Update the camera position.
            m_Camera->GetPosition() += Convert(moveDirection) * velocity;



            //Mouse movement
            MousePosition mousePosition = Input::GetMousePosition();

            if (m_FirstMouseCheck)
            {
                m_LastMousePosition = mousePosition;
                m_FirstMouseCheck = false;
            }

            float xOffset = static_cast<float>(mousePosition.X - m_LastMousePosition.X);
            float yOffset = static_cast<float>(m_LastMousePosition.Y - mousePosition.Y);

            //Reset cursor
            Window& window = Application::Get().GetWindow();
            int width = window.GetWidth(); 
            int height = window.GetHeight();

            Input::SetCursorPosition({ width / 2.0f, height / 2.0f });

            m_LastMousePosition.X = static_cast<float>(width / 2.f);
            m_LastMousePosition.Y = static_cast<float>(height / 2.f);

            xOffset *= m_MouseSensitivity;
            yOffset *= m_MouseSensitivity;

            //Set new settings
            CameraSettings& settings = m_Camera->GetSettings();

            settings.Yaw += xOffset;
            settings.Pitch += yOffset;


            if (settings.Pitch > 89.0f)
                settings.Pitch = 89.0f;
            if (settings.Pitch < -89.0f)
                settings.Pitch = -89.0f;

            m_Camera->UpdateArea();
        }
	}

	void Camera3D::OnEvent(Event& e)
	{
        EventHandler handler(e);

        handler.Handle<KeyPressedEvent>(CR_BIND_EVENT_FN(Camera3D::KeyEvent));
        handler.Handle<MouseButtonPressedEvent>(CR_BIND_EVENT_FN(Camera3D::MousePressedEvent));

        m_Camera->OnEvent(e);
	}

    bool Camera3D::MousePressedEvent(MouseButtonPressedEvent& e)
    {
        if (e.GetMouseButton() == CR_MOUSE_BUTTON_LEFT && m_Escaped)
        {
            m_Escaped = false;
            m_FirstMouseCheck = true;

            Input::SetCursorMode(CR_CURSOR_DISABLED);
        }

        return false;
    }

    bool Camera3D::KeyEvent(KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == CR_KEY_ESCAPE && !m_Escaped)
        {
            m_Escaped = true;

            Input::SetCursorMode(CR_CURSOR_SHOWN);
        }

        return false;
    }

}