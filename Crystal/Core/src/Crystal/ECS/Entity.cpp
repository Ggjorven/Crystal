#include "crpch.h"
#include "Entity.hpp"

namespace Crystal::ECS
{

    Entity::Entity(ECS::Storage& storage, const std::string& name)
        : m_Storage(storage)
    {
        m_UUID = UUIDGenerator::GenerateUUID();
    }

    Entity::~Entity()
    {
		//m_Storage.DeleteEntity(m_UUID);
    }

    Ref<Entity> Entity::Create(ECS::Storage& storage, const std::string& name)
    {
        return CreateRef<Entity>(storage, name);
    }

    Entity& Entity::operator=(const Entity& other)
    {
        if (this != &other) 
        {
            m_DebugName = other.m_DebugName;
            m_Storage = other.m_Storage;
            m_UUID = other.m_UUID;
        }
        return *this;
    }

}