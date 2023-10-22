#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Core/UUID.hpp"

#include <unordered_map>

//Components
#include "Component.hpp"

namespace Crystal::ECS
{

    class Storage
    {
    public:
        //static std::unordered_map<Component::Type, std::unordered_map<CR_UUID, Component>> s_Components;
        static std::unordered_map<CR_UUID, TransformComponent> Storage::s_TransformComponents;

        template<typename T>
        static T& GetComponent(CR_UUID uuid)
        {
            //CR_CORE_ASSERT(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
            //if (Storage::s_Components[T::GetType()][uuid] == Storage::s_Components[T::GetType()].end())
            //{
            //    CR_CORE_ASSERT(false, "Component doesn't Exists");
            //}

            //return Storage::s_Components[T::GetType()][uuid];
        }

        template<>
        static TransformComponent& GetComponent<TransformComponent>(CR_UUID uuid)
        {
            return Storage::s_TransformComponents[uuid];
        }
    };

}
