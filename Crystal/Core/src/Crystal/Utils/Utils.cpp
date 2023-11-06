#include "crpch.h"
#include "Utils.hpp"

#include <cstdlib>

#include "Crystal/Platforms/Windows/WindowsUtilities.hpp"

namespace Crystal
{

	#ifdef CR_PLATFORM_WINDOWS
	Ref<Utils> Utils::s_Instance = CreateRef<WindowsUtils>();
	#endif

	std::string Utils::GetEnviromentVariable(const std::string& key)
	{
		const char* val = std::getenv(key.c_str());
		if (val != nullptr)
			return std::string(val);
		return std::string("");
	}

}