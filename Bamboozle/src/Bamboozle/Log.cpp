#include "Log.h"

#include "Bamboozle/bbzl.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace bbzl
{
    Log::Logger Log::m_coreLogger;
    Log::Logger Log::m_clientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        m_coreLogger = spdlog::stdout_color_mt("BAMBOOZLE");
        m_coreLogger->set_level(spdlog::level::trace);

        m_clientLogger = spdlog::stdout_color_mt("APP");
        m_clientLogger->set_level(spdlog::level::trace);
    }

} // namespace bbzl
