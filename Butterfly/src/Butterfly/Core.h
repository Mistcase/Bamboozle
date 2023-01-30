#pragma once

#ifdef BUTTERFLY_PLATFORM_WINDOWS
	#if BUTTERFLY_DYNAMIC_LINK
		#ifdef BUTTERFLY_BUILD_DLL
			#define BUTTERFLY_API __declspec(dllexport)
		#else
			#define BUTTERFLY_API __declspec(dllimport)
		#endif
	#else
		#define BUTTERFLY_API
	#endif
#else
    #define BUTTERFLY_API
// #error Build platform is not supported!
#endif

#ifdef BUTTERFLY_DEBUG
#define BUTTERFLY_ASSERT(x, ...) { if(!(x)) { BUTTERFLY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_debugtrap(); /*__debugbreak();*/ } }
#define BUTTERFLY_CORE_ASSERT(x, ...) { if(!(x)) { BUTTERFLY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);  __builtin_debugtrap(); /*__debugbreak();*/ } }
#else
#define BUTTERFLY_ASSERT(x, ...)
#define BUTTERFLY_CORE_ASSERT(x, ...)
#endif

#include <memory>

namespace butterfly
{
    template <typename T>
        using Ref = std::shared_ptr<T>;

} // namespace butterfly
