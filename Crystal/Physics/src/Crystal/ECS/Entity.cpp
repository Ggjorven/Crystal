#include "crpch.h"
#include "Entity.hpp"

namespace Crystal::ECS
{

    Entity::Entity()
    {
        m_UUID = UUIDGenerator::GenerateUUID();
    }

    /*
    template<typename T>
    void Entity::AddComponent()
    {
        //Checks
        CR_CORE_ASSERT(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
        if (Storage::s_Components[T::GetType()][m_UUID] == Storage::s_Components[T::GetType()].end())
        {
            CR_CORE_ASSERT(false, "Component doesn't Exists");
        }

        Storage::s_Components[T::GetType()][m_UUID] = T();
    }

    template<typename T>
    void Entity::RemoveComponent()
    {
        //Checks
        CR_CORE_ASSERT(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
        if (Storage::s_Components[T::GetType()][m_UUID] == Storage::s_Components[T::GetType()].end())
        {
            CR_CORE_ASSERT(false, "Component doesn't Exists");
        }

        //TODO removal
    }
    */

}