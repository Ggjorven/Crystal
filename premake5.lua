include "Dependencies.lua"

workspace "Crystal"
	architecture "x86_64"
	startproject "Sandbox"

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
	include "vendor/GLFW"
	include "vendor/ImGui"
group ""

group "Crystal"
	include "Crystal/Core"
group ""

group "Misc"
	include "Sandbox"
group ""
