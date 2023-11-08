include "../../vendor/premake/CSExtensions.lua"

project "Scripting-Engine"
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
