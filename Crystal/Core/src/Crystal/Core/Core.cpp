#include "crpch.h"
#include "Core.hpp"

namespace Crystal
{

	Ref<spdlog::logger>		Log::s_ClientLogger;
	Ref<spdlog::logger>		Log::s_CoreLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] [%L] [%n]: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("CRYSTAL");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}