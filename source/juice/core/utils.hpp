#pragma once

#include "pch.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace juice {

	template<typename T>
	using unqptr = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr unqptr<T> makeunique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr ref<T> MakeRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

    class Log
    {
        public:
            static void Init();

            inline static ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
            inline static ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
        private:
            static ref<spdlog::logger> s_CoreLogger;
            static ref<spdlog::logger> s_ClientLogger;
    };
}

#define BIT(x) (1 << x)
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define __EXIT { exit(-1); }
#define ASSERT(x, ...) { if(!(x)) { JUICE_CORE_ERROR("\n\n[ASSERT]\nError: [{0}(ln: {1})] {2} \nFile: {3}", __FUNCTION__, __LINE__, __VA_ARGS__, __FILE__); __EXIT } }

// Core log macros
#define JUICE_CORE_TRACE(...)       ::juice::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JUICE_CORE_INFO(...)        ::juice::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JUICE_CORE_WARN(...)        ::juice::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JUICE_CORE_ERROR(...)       ::juice::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JUICE_CORE_FATAL(...)       ::juice::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define JUICE_TRACE(...)	        ::juice::Log::GetClientLogger()->trace(__VA_ARGS__)
#define JUICE_INFO(...)	            ::juice::Log::GetClientLogger()->info(__VA_ARGS__)
#define JUICE_WARN(...)	            ::juice::Log::GetClientLogger()->warn(__VA_ARGS__)
#define JUICE_ERROR(...)	        ::juice::Log::GetClientLogger()->error(__VA_ARGS__)
#define JUICE_FATAL(...)	        ::juice::Log::GetClientLogger()->critical(__VA_ARGS__)
