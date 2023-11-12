#pragma once

#include "Crystal/Core/Core.hpp"

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
        ComponentType* GetComponent(CR_UUID uuid)
        {
            //CR_CORE_ASSERT(std::is_base_of<Crystal::ECS::Component, ComponentType>::value, "T must be a subclass of Component");

            auto& componentMap = GetComponentsMap<ComponentType>();
            if (componentMap.find(uuid) != componentMap.end())
            {
                try
                {
                    return &std::any_cast<ComponentType&>(componentMap[uuid]);
                }
                catch (const std::bad_any_cast e)
                {
                    CR_CORE_ASSERT(false, "Component is of the wrong type.");
                }
            }

            return nullptr;
        }

        template<typename ComponentType>
        void AddComponent(CR_UUID uuid, const ComponentType& component)
        {
            auto& componentMap = GetComponentsMap<ComponentType>();
            componentMap[uuid] = component;
        }

        template<typename ComponentType>
        void RemoveComponent(CR_UUID uuid)
        {
            auto& componentMap = GetComponentsMap<ComponentType>();

            auto it = componentMap.find(uuid);
            if (it != componentMap.end())
                componentMap.erase(it);
        }

    public:
        static Coral::HostInstance s_Host;
        //static Coral::AssemblyLoadContext s_Context;

    private:
        template<typename ComponentType>
        std::unordered_map<CR_UUID, std::any>& GetComponentsMap()
        {
            return m_ComponentMaps[typeid(ComponentType)];
        }

    private:
        std::unordered_map<std::type_index, std::unordered_map<CR_UUID, std::any>> m_ComponentMaps;

        Coral::AssemblyLoadContext m_Context;
        Coral::ManagedAssembly m_Assembly;
    };

}