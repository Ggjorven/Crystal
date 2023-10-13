project "Core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"GLEW_STATIC"
	}

	includedirs
	{
		"src",
		"src/Crystal",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.VulkanSDK}"
	}

	links
	{
		"opengl32.lib",
		"%{Library.Vulkan}",
		"GLEW",
		"GLFW",
		"ImGui",
		"spdlog"
	}

	filter "system:windows"
		systemversion "latest"

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