#pragma once

#ifdef BUBBLE_PLATFORM_WINDOWS
	#if BUBBLE_DYNAMIC_LINK
		#ifdef BUBBLE_BUILD_DLL
			#define BUBBLE_API __declspec(dllexport)
		#else
			#define BUBBLE_API __declspec(dllimport)
		#endif
	#else
		#define BUBBLE_API
	#endif
#else
	#error Build platform is not supported!
#endif

#ifdef BUBBLE_ENABLE_ASSERTS
#define BUBBLE_ASSERT(x, ...) { if(!(x)) { BUBBLE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define BUBBLE_CORE_ASSERT(x, ...) { if(!(x)) { BUBBLE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define BUBBLE_ASSERT(x, ...)
#define BUBBLE_CORE_ASSERT(x, ...)
#endif