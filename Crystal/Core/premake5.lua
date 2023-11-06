project "Core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	debuggertype "NativeWithManagedCore" -- for Coral

	architecture "x86_64"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "crpch.h"
	pchsource "src/Crystal/crpch.cpp"

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",
		
		"%{wks.location}/vendor/stb_image/src/stb_image.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"GLEW_STATIC",
		"yaml_cpp_EXPORTS"
	}

	includedirs
	{
		"src",
		"src/Crystal",

		"%{wks.location}/Crystal/Physics/src",

		"%{IncludeDir.GLEW}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.yaml}",
		"%{IncludeDir.Coral}"
	}

    libdirs { "%{wks.location}/vendor/NetCore/7.0.7/" }

	links
	{
		"Physics",

		"opengl32.lib",
		"%{Library.Vulkan}",

		"GLEW",
		"GLFW",
		"ImGui",
		"spdlog",
		"yaml-cpp",
		"Coral.Native"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"

		defines
		{
			"CR_PLATFORM_WINDOWS",
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