#include "crpch.h"
#include "Utils.hpp"

#include <cstdlib>

#include "Crystal/Platforms/Windows/WindowsUtilities.hpp"

namespace Crystal
{

	#ifdef CR_PLATFORM_WINDOWS
	Ref<Utils> Utils::s_Instance = CreateRef<WindowsUtils>();
	#endif

	const std::string& Utils::GetEnviromentVariable(const std::string& key)
	{
		return std::string(std::getenv(key.c_str()));
	}

}