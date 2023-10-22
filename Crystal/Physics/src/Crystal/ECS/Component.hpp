#pragma once

#include "Crystal/Core/UUID.hpp"

#include <glm/glm.hpp>

namespace Crystal::ECS
{

    struct Component //To use as a base to check if a class is part of the components
    {
    public:
        enum class Type
        {
            None = 0,

            Transform
        };

    public:
        inline static Type GetType() { return m_Type; }

    protected:
        static Type m_Type;
    };



    struct TransformComponent : public Component
    {
    public:
        TransformComponent() { m_Type = Type::Transform; }

        glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Size = { 0.0f, 0.0f, 0.0f };
        float Rotation = 0.0f;
    };

}