#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace lit
{
	class Log
	{
	public:
		static void Init()
		{
			spdlog::set_pattern("%^[%T] %n: %v%$");

			coreLogger = spdlog::stdout_color_mt("Engine");
			coreLogger->set_level(spdlog::level::trace);
		}
		static std::shared_ptr<spdlog::logger> coreLogger;
	};
}

#define LOG(...) lit::Log::coreLogger->trace(__VA_ARGS__);
#define LOG_W(...) lit::Log::coreLogger->warn(__VA_ARGS__);
#define LOG_E(...) lit::Log::coreLogger->error(__VA_ARGS__);

