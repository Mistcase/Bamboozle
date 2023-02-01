#pragma once

#include "Butterfly/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace butterfly
{
	class Log
	{
	public:
		using Logger = std::shared_ptr<spdlog::logger>;

	public:
		static void Init();
		inline static Logger GetCoreLogger() { return m_coreLogger; }
		inline static Logger GetClientLogger() { return m_clientLogger; }

	private:
		static Logger m_coreLogger;
		static Logger m_clientLogger;
	};

} // namespace butterfly

// Core log macros
#define BUTTERFLY_CORE_TRACE(...) ::butterfly::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BUTTERFLY_CORE_INFO(...)  ::butterfly::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BUTTERFLY_CORE_WARN(...)  ::butterfly::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BUTTERFLY_CORE_ERROR(...) ::butterfly::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
#define BUTTERFLY_CLIENT_TRACE(...) ::butterfly::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BUTTERFLY_CLIENT_INFO(...)  ::butterfly::Log::GetClientLogger()->info(__VA_ARGS__)
#define BUTTERFLY_CLIENT_WARN(...)  ::butterfly::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BUTTERFLY_CLIENT_ERROR(...) ::butterfly::Log::GetClientLogger()->error(__VA_ARGS__)
