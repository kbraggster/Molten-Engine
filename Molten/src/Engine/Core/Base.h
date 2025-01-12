#pragma once

#include <memory>

#define MLTN_BIND_EVENT_FN(fn)                                                                                         \
    [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

// TODO: Platform specific assertions
#ifdef MLTN_ENABLE_ASSERTS
#define MLTN_ASSERT(x, ...)                                                                                            \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            MLTN_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                          \
            __builtin_debugtrap();                                                                                     \
        }                                                                                                              \
    }
#define MLTN_CORE_ASSERT(x, ...)                                                                                       \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            MLTN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                     \
            __builtin_debugtrap();                                                                                     \
        }                                                                                                              \
    }
#else
#define MLTN_ASSERT(x, ...)
#define MLTN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

template <typename T> using Scope = std::unique_ptr<T>;
template <typename T> using Ref   = std::shared_ptr<T>;