#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace bubble
{
	Log::Logger Log::m_coreLogger;
	Log::Logger Log::m_clientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n %v%$");

		m_coreLogger = spdlog::stdout_color_mt("BUBBLE");
		m_coreLogger->set_level(spdlog::level::trace);

		m_clientLogger = spdlog::stdout_color_mt("APP");
		m_clientLogger->set_level(spdlog::level::trace);
	}

} // namespace bubble