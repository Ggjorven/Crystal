#include "crpch.h"
#include "Storage.hpp"

#include "Crystal/Utils/Utils.hpp"

namespace Crystal::ECS
{

    Coral::HostInstance Storage::s_Host;
    //Coral::AssemblyLoadContext Storage::s_Context;

    Storage::Storage()
    {
        Coral::HostSettings settings;
        settings.CoralDirectory = std::string(Utils::GetEnviromentVariable("CRYSTAL_DIR")) + "\\bin\\Debug-windows-x86_64\\Coral\\";

        s_Host.Initialize(settings);

        //s_Context = s_Host.CreateAssemblyLoadContext("Crystal");
    }

    Storage::~Storage()
    {
        s_Host.Shutdown();
    }

}
