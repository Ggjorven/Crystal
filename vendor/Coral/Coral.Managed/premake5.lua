include "../../premake/CSExtensions.lua"

project "Coral.Managed"
    language "C#"
    dotnetframework "net7.0"
    kind "SharedLib"
	clr "Unsafe"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    configurations { "Debug", "Release", "Dist" }

    propertytags 
    {
        { "AppendTargetFrameworkToOutputPath", "false" },
        { "Nullable", "enable" }
    }

    disablewarnings 
    {
        "CS8500",
        "CS8602",
        "CS8604"
    }

    files 
    {
        "Source/**.cs"
    }

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
