#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#ifdef CR_PLATFORM_WINDOWS
	#include <Windows.h>
#else
	#error Crystal Engine only supports windows at the time.
#endif


#define CR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIT(x) (1 << x)

namespace Crystal
{
	//Pointers
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	//Timestep class to be used to specify amounts of time
	class Timestep
	{
	public:
		Timestep(float timeInSeconds = 0.0f)
			: m_Time(timeInSeconds)
		{
		}

		operator float() const { return m_Time; }

		float& GetSeconds() { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};

	//Logging
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger> GetClientLogger() { return s_ClientLogger; }
		inline static Ref<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }

	private:
		Log() = default; //Makes sure that there can be no instance created of this class
		~Log() = default;

		static Ref<spdlog::logger> s_ClientLogger;
		static Ref<spdlog::logger> s_CoreLogger;
	};

	//Core logging macros
	//#ifndef CR_DIST //Distribution version
	#define CR_CORE_TRACE(...)			Crystal::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define CR_CORE_INFO(...)			Crystal::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define CR_CORE_WARN(...)			Crystal::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define CR_CORE_ERROR(...)			Crystal::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define CR_CORE_CRITICAL(...)		Crystal::Log::GetCoreLogger()->critical(__VA_ARGS__)

	/*
	#else
	#define CR_CORE_TRACE(...)			
	#define CR_CORE_INFO(...)			
	#define CR_CORE_WARN(...)			
	#define CR_CORE_ERROR(...)			
	#define CR_CORE_CRITICAL(...)		

	#endif
	*/

	//Client logging macros
	#define CR_TRACE(...)			Crystal::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define CR_INFO(...)			Crystal::Log::GetClientLogger()->info(__VA_ARGS__)
	#define CR_WARN(...)			Crystal::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define CR_ERROR(...)			Crystal::Log::GetClientLogger()->error(__VA_ARGS__)
	#define CR_CRITICAL(...)		Crystal::Log::GetClientLogger()->critical(__VA_ARGS__)

	//Assert
	#define CR_CORE_ASSERT(x, ...) if(!(x)) {\
										CR_CORE_CRITICAL(__VA_ARGS__);\
										__debugbreak(); }
}