#pragma once

#include "Core.h"

#if defined(DEBUG)
    #if defined(BBZL_PLATFORM_WINDOWS)
        #define DEBUG_BREAK __debugbreak
    #elif defined(BBZL_PLATFORM_APPLE) || defined(BBZL_PLATFORM_LINUX)
        #define DEBUG_BREAK __builtin_trap
    #else
        #define DEBUG_BREAK std::abort();
    #endif

    #define ASSERT(x, ...)								        \
	{															\
		 if (!(x))												\
		 {									                    \
			 DEBUG_BREAK();										\
		 }														\
	}

    #define ASSERT_FAIL(msg) ASSERT(false)
#else
    #define ASSERT(x, ...)
    #define ASSERT_FAIL(msg)
#endif
