#include "crpch.h"
#include "Storage.hpp"

#include "Crystal/Core/UUID.hpp"

#include "Crystal/Core/Application.hpp"
#include "Crystal/Utils/Utils.hpp"
#include "Crystal/Scripting/Wrapper/SetupInternalCalls.hpp"

#include "Crystal/Data/Project/Project.hpp"

namespace Crystal::ECS
{

    Coral::HostInstance                     Storage::s_Host;
    Coral::AssemblyLoadContext              Storage::s_LoadContext;
    std::vector<Coral::ManagedAssembly>     Storage::s_Assemblies = { };
    std::vector<std::filesystem::path>      Storage::s_AssemblyPaths = { };

    uint32_t                                Storage::s_StorageCount = 0u;
    Coral::AssemblyLoadContext              Storage::s_Context;
    Coral::ManagedAssembly                  Storage::s_Assembly;

    static void CoralMessageCallback(Coral::NativeString message, Coral::MessageLevel level)
    {
        switch (level)
        {
        case Coral::MessageLevel::Info:
            //CR_CORE_TRACE("(Coral) {0}", std::string(message));
            break;
        case Coral::MessageLevel::Warning:
            CR_CORE_WARN("(Coral) {0}", std::string(message));
            break;
        case Coral::MessageLevel::Error:
            CR_CORE_ERROR("(Coral) {0}", std::string(message));
            break;
        }
    }

    Storage::Storage()
    {
        //CR_CORE_TRACE("Storage");
        if (s_StorageCount == 0u)
        {
            Coral::HostSettings settings;
            settings.MessageCallback = CoralMessageCallback;
            settings.CoralDirectory = Application::GetWorkingDirectory().string() + "\\";

            s_Host = Coral::HostInstance();
            s_Host.Initialize(settings);

            s_Context = s_Host.CreateAssemblyLoadContext("Crystal-Engine");
            s_LoadContext = s_Host.CreateAssemblyLoadContext("Crystal-Assemblies");

            s_Assembly = s_Context.LoadAssembly((Application::GetWorkingDirectory().string() + "\\Scripting-Engine.dll"));

            Wrapper::Setup::Run(s_Assembly);
        }
        else
        {
            s_Host.UnloadAssemblyLoadContext(s_LoadContext);
            s_LoadContext = s_Host.CreateAssemblyLoadContext("Crystal-Assemblies");
        }
        ++s_StorageCount;
    }

    Storage::~Storage()
    {
        //CR_CORE_TRACE("~Storage");
        --s_StorageCount;

        s_Assemblies.clear();
        s_AssemblyPaths.clear();

        m_ComponentMaps.clear();

        if (s_StorageCount == 0u)
        {
            //CR_CORE_TRACE("~Storage - Shutdown");
            s_Host.UnloadAssemblyLoadContext(s_LoadContext);
            s_Host.UnloadAssemblyLoadContext(s_Context);
            s_Host.Shutdown();
        }
    }

    void Storage::LoadAssembly(std::filesystem::path path)
    {
        //s_AssemblyPaths.emplace_back(path);
        s_Assemblies.emplace_back(s_LoadContext.LoadAssembly(path.string()));
    }

    void Storage::ReloadAssemblies()
    {
        s_Assemblies.clear();
        std::vector<std::filesystem::path> copy = s_AssemblyPaths;
        s_AssemblyPaths.clear();

        for (auto& script : GetComponentsMap<ECS::ScriptComponent>())
        {
            auto& scriptC = GetComponent<ECS::ScriptComponent>(script.first);
            scriptC.Script->DestroyObject(); 
        }

        // Reload context
        s_Host.UnloadAssemblyLoadContext(s_LoadContext);
        s_LoadContext = s_Host.CreateAssemblyLoadContext("Crystal-Assemblies");

        for (auto& path : copy)
        {
            std::filesystem::path projDir = Project::GetCurrentProject()->GetProjectDir();
            std::filesystem::path scriptDir = Project::GetCurrentProject()->GetScriptsDir();
            AddPath(path);
            LoadAssembly(projDir / scriptDir / path);
        }

        for (auto& script : GetComponentsMap<ECS::ScriptComponent>())
        {
            auto& scriptC = GetComponent<ECS::ScriptComponent>(script.first);
            scriptC.Script->Reload();
        }
    }

    void Storage::DestroyObjects()
    {
        for (auto& script : GetComponentsMap<ECS::ScriptComponent>())
        {
            auto& scriptC = GetComponent<ECS::ScriptComponent>(script.first);
            scriptC.Script->DestroyObject();
        }
    }

    void Storage::DeleteEntity(CR_UUID uuid)
    {
        // Remove all components
		RemoveComponent<ECS::TagComponent>(uuid);
		RemoveComponent<ECS::TransformComponent>(uuid);
		RemoveComponent<ECS::Renderer2DComponent>(uuid);
		RemoveComponent<ECS::Renderer3DComponent>(uuid);
		RemoveComponent<ECS::ScriptComponent>(uuid);
		RemoveComponent<ECS::ColliderComponent>(uuid);
		RemoveComponent<ECS::CameraComponent2D>(uuid);
		RemoveComponent<ECS::CameraComponent3D>(uuid);
    }

}
