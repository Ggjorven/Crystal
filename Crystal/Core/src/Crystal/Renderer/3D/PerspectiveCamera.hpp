#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Events/Events.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Crystal
{
    
    struct MovementArea
    {
    public:
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;

        MovementArea(const glm::vec3& front, const glm::vec3& up, const glm::vec3& right)
            : Front(front), Up(up), Right(right)
        {
        }
    };

    struct CameraSettings
    {
    public:
        float Yaw;
        float Pitch;
        float FOV;

        CameraSettings(float yaw, float pitch, float fov)
            : Yaw(yaw), Pitch(pitch), FOV(fov)
        {
        }
    };

    class PerspectiveCamera
    {
    public:
        PerspectiveCamera(float width, float height);
        virtual ~PerspectiveCamera();

        void OnUpdate(Timestep& ts);
        void OnEvent(Event& e);

        void UpdateArea();

        glm::vec3& GetPosition() { return m_Position; }
        
        MovementArea& GetArea() { return m_Area; }
        CameraSettings& GetSettings() { return m_Properties; }

        glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
        glm::mat4 GetProjectionMatrix() const { return m_ViewMatrix; }
        glm::mat4 GetViewProjectionMatrix() const { return m_ProjectionMatrix * m_ViewMatrix; }

        void SetViewMatrix(const glm::mat4& view) { m_ViewMatrix = view; m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; }
        void SetProjectionMatrix(const glm::mat4& projection) { m_ProjectionMatrix = projection; m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; }
        void SetViewProjectionMatrix(const glm::mat4& viewProjectionMatrix) { m_ViewProjectionMatrix = viewProjectionMatrix; }

    private:
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        MovementArea m_Area;
        CameraSettings m_Properties;

        float m_AspectRatio;
    };
    
}