#pragma once

#if 0

#    if defined(BBZL_PLATFORM_WINDOWS)
#        define DEBUG_BREAK __debugbreak
#    else
#        define DEBUG_BREAK __builtin_debugtrap
#    endif

#    define BBZL_ASSERT(x, ...)                                   \
        {                                                              \
            if (!(x))                                                  \
            {                                                          \
                BBZL_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
                DEBUG_BREAK();                                         \
            }                                                          \
        }
#    define BBZL_CORE_ASSERT(x, ...)                                   \
        {                                                                   \
            if (!(x))                                                       \
            {                                                               \
                BBZL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
                DEBUG_BREAK();                                              \
            }                                                               \
        }
#else
#    define BBZL_ASSERT(x, ...)
#    define BBZL_CORE_ASSERT(x, ...)
#endif

#include <memory>

namespace bbzl
{
    template <typename T>
    using Ref = std::shared_ptr<T>;

} // namespace bbzl
