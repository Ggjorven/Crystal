include "Dependencies.lua"

workspace "Crystal"
	architecture "x86_64"
	startproject "Project-2D"

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
	include "vendor/yaml-cpp"
group ""

group "Crystal"
	group "Crystal/Engine"
		include "Crystal/Core"
		include "Crystal/Physics"
	group "Crystal"
	include "Crystalizer"
group ""

group "Misc"
	include "Projects/Project-2D"
	include "Projects/Project-3D"
group ""
