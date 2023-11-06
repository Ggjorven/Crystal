#pragma once

#include "Crystal/Core/Core.hpp"

#include <string>

namespace Crystal
{

	class Utils
	{
	public:
		
		//These return empty strings if cancelled
		static std::string OpenFile(const char* filter) { return s_Instance->OpenFileImplementation(filter); }
		static std::string SaveFile(const char* filter) { return s_Instance->SaveFileImplementation(filter); }
		
		static float GetTime() { return s_Instance->GetTimeImplementation(); }

		static std::string GetEnviromentVariable(const std::string& key);

	private:
		virtual std::string OpenFileImplementation(const char* filter) = 0;
		virtual std::string SaveFileImplementation(const char* filter) = 0;

		virtual float GetTimeImplementation() = 0;

	private:
		static Ref<Utils> s_Instance;
	};

}
