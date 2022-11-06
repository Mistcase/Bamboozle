#pragma once

#include "Bubble/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace bubble
{
	class BUBBLE_API Log
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

} // namespace bubble

// Core log macros
#define BUBBLE_CORE_TRACE(...) ::bubble::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BUBBLE_CORE_INFO(...)  ::bubble::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BUBBLE_CORE_WARN(...)  ::bubble::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BUBBLE_CORE_ERROR(...) ::bubble::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
#define BUBBLE_CLIENT_TRACE(...) ::bubble::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BUBBLE_CLIENT_INFO(...)  ::bubble::Log::GetClientLogger()->info(__VA_ARGS__)
#define BUBBLE_CLIENT_WARN(...)  ::bubble::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BUBBLE_CLIENT_ERROR(...) ::bubble::Log::GetClientLogger()->error(__VA_ARGS__)
