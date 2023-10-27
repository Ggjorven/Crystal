#include "crpch.h"
#include "Entity.hpp"

namespace Crystal::ECS
{

    Entity::Entity(ECS::Storage& storage, const std::string& name)
        : m_Storage(storage)
    {
        m_UUID = UUIDGenerator::GenerateUUID();
    }

    Ref<Entity> Entity::Create(ECS::Storage& storage, const std::string& name)
    {
        Ref<Entity> entity = CreateRef<Entity>(storage, name);
        return entity;
    }

}