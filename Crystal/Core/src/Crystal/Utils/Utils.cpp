#include "crpch.h"
#include "Utils.hpp"

#include "Crystal/Platforms/Windows/WindowsUtilities.hpp"

namespace Crystal
{

	#ifdef CR_PLATFORM_WINDOWS
	Ref<Utils> Utils::s_Instance = CreateRef<WindowsUtils>();
	#endif

}