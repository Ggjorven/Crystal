project "spdlog"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/async.cpp",
		"src/bundled_fmtlib_format.cpp",
		"src/cfg.cpp",
		"src/color_sinks.cpp",
		"src/file_sinks.cpp",
		"src/spdlog.cpp",
		"src/stdout_sinks.cpp"
	}
	
	includedirs
	{
		"include"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS",
		"SPDLOG_COMPILED_LIB"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
