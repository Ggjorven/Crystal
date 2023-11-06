local CoralDotNetPath = os.getenv("CORAL_DOTNET_PATH")

project "Coral.Native"
    language "C++"
    cppdialect "C++20"
    kind "StaticLib"
    staticruntime "On"

    architecture "x86_64"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "CoralPCH.hpp"
    pchsource "Source/CoralPCH.cpp"

    forceincludes { "CoralPCH.hpp" }

    files 
    {
        "Source/**.cpp",
        "Source/**.hpp",

        "Include/Coral/**.hpp",
    }

    includedirs 
    { 
        "Source/",
        "Include/Coral/",
        
        "%{wks.location}/vendor/NetCore/7.0.7/"
    }

    libdirs { "%{wks.location}/vendor/NetCore/7.0.7/" }

	links
	{
        "libnethost.lib",
		"nethost.lib"
	}

    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "On"

    filter { "configurations:Release" }
        runtime "Release"
        symbols "Off"
        optimize "On"
