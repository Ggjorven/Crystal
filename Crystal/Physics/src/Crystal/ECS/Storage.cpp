#include "crpch.h"
#include "Storage.hpp"

#include "Crystal/Utils/Utils.hpp"

#include "Crystal/Scripting/Wrapper/SetupInternalCalls.hpp"

namespace Crystal::ECS
{

    Coral::HostInstance Storage::s_Host;
    //Coral::AssemblyLoadContext Storage::s_Context;

    Storage::Storage()
    {
        Coral::HostSettings settings;
        settings.CoralDirectory = std::string(Utils::GetEnviromentVariable("CRYSTAL_DIR")) + "\\bin\\Debug-windows-x86_64\\Coral\\";

        s_Host.Initialize(settings);

        m_Context = s_Host.CreateAssemblyLoadContext("Crystal");
        m_Assembly = m_Context.LoadAssembly(Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Debug-windows-x86_64\\Coral\\") + "Scripting-Engine.dll");
        Wrapper::Setup::Run(m_Assembly);
    }

    Storage::~Storage()
    {
        s_Host.Shutdown();
    }

}
