#include "crpch.h"
#include "Storage.hpp"

#include "Crystal/Core/Application.hpp"
#include "Crystal/Utils/Utils.hpp"
#include "Crystal/Scripting/Wrapper/SetupInternalCalls.hpp"

namespace Crystal::ECS
{

    Coral::HostInstance Storage::s_Host;

    static void CoralMessageCallback(Coral::NativeString message, Coral::MessageLevel level)
    {
        switch (level)
        {
        case Coral::MessageLevel::Info:
            CR_CORE_TRACE("(Coral) {0}", std::string(message));
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
        Coral::HostSettings settings;
        settings.MessageCallback = CoralMessageCallback;
        settings.CoralDirectory = Application::GetWorkingDirectory().string() + "\\";

        s_Host.Initialize(settings);

        m_Context = s_Host.CreateAssemblyLoadContext("Crystal");
        m_Assembly = m_Context.LoadAssembly(Application::GetWorkingDirectory().string() + "\\Scripting-Engine.dll");
        Wrapper::Setup::Run(m_Assembly);
    }

    Storage::~Storage()
    {
        s_Host.Shutdown();
    }

}
