#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Data/Project/Project.hpp"

#include <filesystem>

namespace Crystal 
{

	class ScriptBuilder
	{
	public:
		static void BuildCSProject(const std::filesystem::path& filepath);
		static void BuildScriptAssembly(Ref<Project> project);
	};

}
