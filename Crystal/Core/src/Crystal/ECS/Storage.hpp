#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/Utils.hpp"

#include "Crystal/Core/UUID.hpp"

#include <Coral/HostInstance.hpp>
#include <Coral/GC.hpp>
#include <Coral/NativeArray.hpp>
#include <Coral/Attribute.hpp>

#include <any>
#include <unordered_map>
#include <map>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <functional>
#include <optional>

#include "Component.hpp"

namespace Crystal::ECS
{

    class Storage
    {
    public:
        Storage();
        virtual ~Storage();

        template<typename ComponentType>
        bool HasComponent(CR_UUID uuid)
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be a subclass of Component");

            auto& componentMap = GetComponentsMap<ComponentType>();
            if (componentMap.find(uuid) != componentMap.end())
                return true;
            
            return false;
        }

        template<typename ComponentType>
        ComponentType& GetComponent(CR_UUID uuid)
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be a subclass of Component");

            auto& componentMap = GetComponentsMap<ComponentType>();
            if (componentMap.find(uuid) != componentMap.end())
            {
                return static_cast<ComponentType&>(componentMap[uuid]);
            }

            auto temp = ComponentType();
            return temp;
        }

        template<typename ComponentType>
        ComponentType& AddComponent(CR_UUID uuid, const ComponentType& component = ComponentType())
        {
            CR_CORE_TRACE("Add");
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be a subclass of Component");

            auto& componentMap = GetComponentsMap<ComponentType>();
            componentMap[uuid] = component;

            return GetComponent<ComponentType>(uuid);
            CR_CORE_TRACE("~Add");
        }

        template<typename ComponentType>
        void RemoveComponent(CR_UUID uuid)
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be a subclass of Component");

            auto& componentMap = GetComponentsMap<ComponentType>();

            auto it = componentMap.find(uuid);
            if (it != componentMap.end())
            {
                componentMap.erase(it);
            }
        }

    public:
        static Coral::HostInstance s_Host;

    private:
        template<typename ComponentType>
        std::unordered_map<CR_UUID, ComponentType>& GetComponentsMap()
        {
            auto typeIndex = typeid(ComponentType);

            if (m_ComponentMaps.find(typeIndex) == m_ComponentMaps.end())
            {
                m_ComponentMaps[typeIndex] = std::unordered_map<CR_UUID, ComponentType>();
            }

            return std::any_cast<std::unordered_map<CR_UUID, ComponentType>&>(m_ComponentMaps[typeIndex]);
        }

    private:
        std::unordered_map<std::type_index, std::unordered_map<CR_UUID, std::any>> m_ComponentMaps;

        Coral::AssemblyLoadContext m_Context;
        Coral::ManagedAssembly m_Assembly;
    };

}