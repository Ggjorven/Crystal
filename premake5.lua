include "Dependencies.lua"

premake.api.addAllowed("debuggertype", "NativeWithManagedCore") -- For Coral

workspace "Crystal"
	-- cant specify architecture "x86_64" because of Coral
	startproject "Crystalizer"

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

group "Additional Dependencies"
	group "Additional Dependencies/Coral"
		include "vendor/Coral/Coral.Managed"
		include "vendor/Coral/Coral.Native"
group "Additional Dependencies"
	include "vendor/GLEW"
	include "vendor/GLFW"
	include "vendor/ImGui"
	include "vendor/spdlog"
	include "vendor/yaml-cpp"
group ""

group "Crystal"
	include "Crystal/Core"
	include "Crystal/Physics"
	include "Crystal/Scripting"
group ""

group "Tools"
	include "Crystalizer/Launcher"
	include "Crystalizer"
	include "Runtime"
group ""