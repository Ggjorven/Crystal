include "../../vendor/premake/CSExtensions.lua"

project "Scripting-Engine"
    language "C#"
    dotnetframework "net7.0"
    kind "SharedLib"
	clr "Unsafe"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    configurations { "Debug", "Release", "Dist" }

    propertytags 
    {
        { "AppendTargetFrameworkToOutputPath", "true" },
        { "Nullable", "enable" }
    }

    disablewarnings 
    {
        "CS8500",
        "CS0649"
    }

    files 
    {
        "src/**.cs"
    }

    links
    {
        "Coral.Managed"
    }

    -- postbuildcommands
    -- {
    --     '{COPYFILE} "%{wks.location}/bin/" .. outputdir .. "Scripting-Engine.dll" "%{cfg.targetdir}"',
    -- }

    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "On"

    filter { "configurations:Release" }
        runtime "Release"
        symbols "Off"
        optimize "On"

    filter { "configurations:Dist" }
        runtime "Release"
        symbols "Off"
        optimize "On"