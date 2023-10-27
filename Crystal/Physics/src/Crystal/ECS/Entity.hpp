#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Core/UUID.hpp"

#include "Crystal/ECS/Component.hpp"
#include "Crystal/ECS/Storage.hpp"

#include <string>
#include <type_traits> 

namespace Crystal::ECS
{

    class Entity
    {
    public:
        Entity(ECS::Storage& storage, const std::string& name = "Entity");
        virtual ~Entity() = default;

        template <typename ComponentType>
        inline void AddComponent(ComponentType component = ComponentType())
        {
            m_Storage.AddComponent<ComponentType>(m_UUID, component);
        }

        template <typename ComponentType>
        inline void RemoveComponent()
        {
            m_Storage.RemoveComponent<ComponentType>(m_UUID);
        }

        template <typename ComponentType>
        inline ComponentType& GetComponent()
        {
            return m_Storage.GetComponent<ComponentType>(m_UUID);
        }

        inline const CR_UUID GetUUID() const { return m_UUID; }

        static Ref<Entity> Create(ECS::Storage& storage, const std::string& name = "Entity");

    protected:
        ECS::Storage& m_Storage;

        std::string m_DebugName;
        CR_UUID m_UUID;
    };

}
