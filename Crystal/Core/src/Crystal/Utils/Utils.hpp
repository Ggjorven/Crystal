#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Utils/CustomTypes.hpp"

#include <string>
#include <Windows.h> // TODO(Jorben): Add another way of getting display size that's not only for Windows

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

		static Vec2<float> GetDisplaySize() { return Vec2<float>((float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN)); }

	private:
		virtual std::string OpenFileImplementation(const char* filter) = 0;
		virtual std::string SaveFileImplementation(const char* filter) = 0;

		virtual float GetTimeImplementation() = 0;

	private:
		static Ref<Utils> s_Instance;
	};

}
