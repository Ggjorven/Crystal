include "Dependencies.lua"

workspace "Crystal"
	architecture "x86_64"
	startproject "Mario"

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
	include "vendor/GLEW"
	include "vendor/GLFW"
	include "vendor/ImGui"
	include "vendor/spdlog"
group ""

group "Crystal"
	include "Crystal/Core"
group ""

group "Misc"
	include "Mario"
group ""
