#pragma once

#if defined(BUTTERFLY_DEBUG)

#    if defined(BUTTERFLY_PLATFORM_WINDOWS)
#        define DEBUG_BREAK __debugbreak
#    else
#        define DEBUG_BREAK __builtin_debugtrap
#    endif

#    define BUTTERFLY_ASSERT(x, ...)                                   \
        {                                                              \
            if (!(x))                                                  \
            {                                                          \
                BUTTERFLY_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
                DEBUG_BREAK();                                         \
            }                                                          \
        }
#    define BUTTERFLY_CORE_ASSERT(x, ...)                                   \
        {                                                                   \
            if (!(x))                                                       \
            {                                                               \
                BUTTERFLY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
                DEBUG_BREAK();                                              \
            }                                                               \
        }
#else
#    define BUTTERFLY_ASSERT(x, ...)
#    define BUTTERFLY_CORE_ASSERT(x, ...)
#endif

#include <memory>

namespace butterfly
{
    template <typename T>
    using Ref = std::shared_ptr<T>;

} // namespace butterfly
