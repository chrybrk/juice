#include "utils.hpp"

namespace juice {
	ref<spdlog::logger> Log::s_CoreLogger;
	ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() 
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("JUICE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
