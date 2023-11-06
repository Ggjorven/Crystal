include "../../../../vendor/premake/CSExtensions.lua"

-- TODO? workspace "Test.Project"

workspace "Project"
	-- cant specify architecture "x86_64" because of Coral
	startproject "Script"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Script"
    language "C#"
    dotnetframework "net7.0"
    kind "SharedLib"
	clr "Unsafe"
	
    propertytags {
        { "AppendTargetFrameworkToOutputPath", "false" },
        { "Nullable", "enable" }
    }

    files {
        "src/**.cs"
    }
    
    links { "Coral.Managed" }
