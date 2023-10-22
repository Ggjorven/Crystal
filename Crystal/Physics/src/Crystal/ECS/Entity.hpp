#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Core/UUID.hpp"

#include "Crystal/ECS/Component.hpp"
#include "Crystal/ECS/Storage.hpp"

#include <type_traits> 

namespace Crystal::ECS
{

    class Entity
    {
    public:
        Entity();
        virtual ~Entity() = default;

        //TODO fix

        // Add a component of type T to the entity
        template <typename T>
        inline void AddComponent()
        {
            //Checks
            //CR_CORE_ASSERT(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
            //if (Storage::s_Components[T::GetType()][m_UUID] == Storage::s_Components[T::GetType()].end())
            //{
            //    CR_CORE_ASSERT(false, "Component doesn't Exists");
            //}

            //Storage::s_Components[T::GetType()][m_UUID] = T();
        }

        template<>
        inline void AddComponent<TransformComponent>()
        {
            Storage::s_TransformComponents[m_UUID] = TransformComponent();
        }


        // Remove a component of type T from the entity
        template <typename T>
        inline void RemoveComponent()
        {
            //Checks
            //CR_CORE_ASSERT(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
            //if (Storage::s_Components[T::GetType()][m_UUID] == Storage::s_Components[T::GetType()].end())
            //{
            //    CR_CORE_ASSERT(false, "Component doesn't Exists");
            //}

            //TODO removal
        }

        inline const CR_UUID GetUUID() const { return m_UUID; }

    protected:
        CR_UUID m_UUID;
    };

}
