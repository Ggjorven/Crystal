#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Renderer/3D/PerspectiveCamera.hpp"

#include "Crystal/Core/Events/Input/Input.hpp"

namespace Crystal
{

    class Camera3D
    {
    public:
        Camera3D(float width, float height);
        virtual ~Camera3D();

        void OnUpdate(Timestep& ts);
        void OnEvent(Event& e);

        inline Ref<PerspectiveCamera>& GetCamera() { return m_Camera; }

    private:
        bool MousePressedEvent(MouseButtonPressedEvent& e);
        bool KeyEvent(KeyPressedEvent& e);

    private:
        Ref<PerspectiveCamera> m_Camera;

        bool m_Escaped;
        bool m_FirstMouseCheck;

        MousePosition m_LastMousePosition;

        float m_MovementSpeed;
        float m_MouseSensitivity;
    };

}