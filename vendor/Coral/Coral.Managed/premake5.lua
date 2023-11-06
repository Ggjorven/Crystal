include "../../premake/CSExtensions.lua"

project "Coral.Managed"
    language "C#"
    dotnetframework "net7.0"
    kind "SharedLib"
	clr "Unsafe"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    propertytags 
    {
        { "AppendTargetFrameworkToOutputPath", "false" },
        { "Nullable", "enable" }
    }

    disablewarnings 
    {
        "CS8500"
    }

    files 
    {
        "Source/**.cs"
    }
