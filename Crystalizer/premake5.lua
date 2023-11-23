project "Crystalizer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	
	debuggertype "NativeWithManagedCore" -- for Coral
	debugdir "$(TargetDir)"

	architecture "x86_64"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"src/Sandbox",
		"src/Sandbox/2D",
		"src/Sandbox/3D",

		"%{wks.location}/Crystal/Core/src",
		"%{wks.location}/Crystal/Physics/src",
		"%{wks.location}vendor",

		"%{IncludeDir.GLEW}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.yaml}",
		"%{IncludeDir.Coral}",
	}

	disablewarnings
	{
		"4312"
	}

	libdirs { "%{wks.location}/vendor/NetCore/7.0.7/" }
	
	links
	{
		"Core",

		"nethost.lib",
		"libnethost.lib"
	}

	postbuildcommands
	{
		'{COPYFILE} "%{wks.location}/vendor/NetCore/7.0.7/nethost.dll" "%{cfg.targetdir}"',
        '{COPYFILE} "%{wks.location}/vendor/Coral/Coral.Managed/Coral.Managed.runtimeconfig.json" "%{cfg.targetdir}"',

        '{COPYFILE} "%{wks.location}/bin/Release-%{cfg.system}-/Coral.Managed/Coral.Managed.dll" "%{cfg.targetdir}"',
        '{COPYFILE} "%{wks.location}/bin/Release-%{cfg.system}-/Scripting-Engine/Scripting-Engine.dll" "%{cfg.targetdir}"'
    }

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"

		defines
		{
			"CR_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"GLEW_STATIC"
		}

	filter "configurations:Debug"
		defines "CR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CR_DIST"
		runtime "Release"
		optimize "on"
