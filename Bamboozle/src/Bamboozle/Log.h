#pragma once

#include "Bamboozle/Core.h"
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace bbzl
{
    class Log
    {
    public:
        using Logger = std::shared_ptr<spdlog::logger>;

    public:
        static void Init();
        inline static Logger GetCoreLogger()
        {
            return m_coreLogger;
        }
        inline static Logger GetClientLogger()
        {
            return m_clientLogger;
        }

    private:
        static Logger m_coreLogger;
        static Logger m_clientLogger;
    };

} // namespace bbzl

// Core log macros
#define BBZL_CORE_TRACE(...) ::bbzl::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BBZL_CORE_INFO(...) ::bbzl::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BBZL_CORE_WARN(...) ::bbzl::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BBZL_CORE_ERROR(...) ::bbzl::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
#define BBZL_CLIENT_TRACE(...) ::bbzl::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BBZL_CLIENT_INFO(...) ::bbzl::Log::GetClientLogger()->info(__VA_ARGS__)
#define BBZL_CLIENT_WARN(...) ::bbzl::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BBZL_CLIENT_ERROR(...) ::bbzl::Log::GetClientLogger()->error(__VA_ARGS__)
