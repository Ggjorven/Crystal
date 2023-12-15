#include "crpch.h"
#include "Utils.hpp"

#include <cstdlib>

#include <imgui.h>
#include <imgui_internal.h>

#include "Crystal/Platforms/Windows/WindowsUtilities.hpp"

namespace Crystal
{

	#ifdef CR_PLATFORM_WINDOWS
	Ref<Utils> Utils::s_Instance = CreateRef<WindowsUtils>();
	#endif

	void Utils::ReplaceBackSlashes(std::string& path)
	{
		size_t found = path.find("\\");
		while (found != std::string::npos) 
		{
			// Check if there is a character after the double backslashes
			if (found + 1 < path.size())
			{
				path.replace(found, 1, "\\");  // Replace only the first backslash
				found = path.find("\\", found + 1);
			}
			else 
			{
				break;  // Break if there is no character after the double backslashes
			}
		}
	}

	std::string Utils::GetEnviromentVariable(const std::string& key)
	{
		const char* val = std::getenv(key.c_str());
		if (val != nullptr)
			return std::string(val);
		return std::string("");
	}

	std::string Utils::GetImGuiSettings()
	{
		size_t size;
		const char* data = ImGui::SaveIniSettingsToMemory(&size);

		// Convert the memory buffer to a std::string
		std::string iniSettings(data, size);

		return iniSettings;
	}

}