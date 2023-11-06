#include "crpch.h"
#include "Storage.hpp"

namespace Crystal::ECS
{

    //MonoDomain* Storage::s_ScriptingDomain = nullptr;

    Storage::Storage()
    {
        // Initialize the Mono runtime
        //s_ScriptingDomain = mono_jit_init("CSharpInterop");

        // Create a new Mono domain
        //s_ScriptingDomain = mono_domain_create();
    }

    Storage::~Storage()
    {
        // Unload the Mono domain and its assemblies
        //mono_domain_unload(s_ScriptingDomain);

        // Clean up the Mono runtime
        //mono_jit_cleanup(s_ScriptingDomain);
    }

}
