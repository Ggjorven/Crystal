#pragma once

#pragma warning(push)
#pragma warning(disable : 4172) // For the temp variable in GetComponent

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/Utils.hpp"
#include "Crystal/Core/UUID.hpp"
#include "Crystal/ECS/Component.hpp"

#include <any>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <optional>

namespace Crystal
{
    class Scene;
    class Scene2D;
    class Scene3D;
    class SceneRenderer2D;
    class SceneRenderer3D;
}

namespace Crystal::ECS
{
    class Storage
    {
    public:
        Storage();
        virtual ~Storage();

        template <typename ComponentType>
        bool HasComponent(CR_UUID uuid)
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be a subclass of Component");

            auto& componentMap = GetComponentsMap<ComponentType>();
            return componentMap.find(uuid) != componentMap.end();
        }

        template<typename ComponentType>
        ComponentType& GetComponent(CR_UUID uuid)
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be a subclass of Component");

            auto& componentMap = GetComponentsMap<ComponentType>();
            if (componentMap.find(uuid) != componentMap.end())
            {
                try
                {
                    return std::any_cast<ComponentType&>(componentMap[uuid]);
                }
                catch (const std::bad_any_cast e)
                {
                    CR_CORE_ASSERT(false, "Component is of the wrong type.");
                }
            }

            // Note(Jorben): You should never use this...
            ComponentType temp = ComponentType();
            return temp;
        }

        template<typename ComponentType>
        ComponentType& AddComponent(CR_UUID uuid, const ComponentType& component = ComponentType())
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be a subclass of Component");

            auto& componentMap = GetComponentsMap<ComponentType>();
            componentMap[uuid] = component;

            return GetComponent<ComponentType>(uuid);
        }

        template<typename ComponentType>
        void RemoveComponent(CR_UUID uuid)
        {
            static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must be a subclass of Component");

            auto& componentMap = GetComponentsMap<ComponentType>();

            auto it = componentMap.find(uuid);
            if (it != componentMap.end())
                componentMap.erase(it);
        }

        void AddPath(std::filesystem::path path) { s_AssemblyPaths.emplace_back(path); }
        void LoadAssembly(std::filesystem::path path);
        void ReloadAssemblies();

    public:
        static Coral::HostInstance s_Host;
        static Coral::AssemblyLoadContext s_LoadContext;
        static std::vector<Coral::ManagedAssembly> s_Assemblies;
        static std::vector<std::filesystem::path> s_AssemblyPaths;

    private:
        template<typename ComponentType>
        std::unordered_map<CR_UUID, std::any>& GetComponentsMap()
        {
            return m_ComponentMaps[typeid(ComponentType)];
        }

    private:
        std::unordered_map<std::type_index, std::unordered_map<CR_UUID, std::any>> m_ComponentMaps;

        static uint32_t s_StorageCount;
        static Coral::AssemblyLoadContext s_Context;
        static Coral::ManagedAssembly s_Assembly;

        friend class Scene;
        friend class Scene2D;
        friend class Scene3D;
        friend class SceneRenderer2D;
        friend class SceneRenderer3D;
    };
}

#pragma warning(pop)