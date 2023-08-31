#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define BBZL_PLATFORM_WINDOWS
#elif __APPLE__
    #define BBZL_PLATFORM_APPLE
    #include <TargetConditionals.h>

    #if TARGET_IPHONE_SIMULATOR
         #define BBZL_PLATFORM_MOBILE_SIMULATOR
    #elif TARGET_OS_MACCATALYST
         #define PLATFORM_UNKNOWN
    #elif TARGET_OS_IPHONE
        #define BBZL_PLATFORM_IOS
    #elif TARGET_OS_MAC
        #define BBZL_PLATFORM_MACOS
    #else
        #error "Unknown Apple platform"
    #endif
#elif __ANDROID__
    #define BBZL_PLATFORM_ANDROID
#elif __linux__
    #define BBZL_PLATFORM_LINUX
#else
    #error "Unknown compiler"
#endif

#include "Bamboozle/Ref.h"
