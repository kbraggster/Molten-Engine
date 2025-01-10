#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Log
{
  public:
    static void Init();

    static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

  private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

// Core log macros
#define MLTN_CORE_TRACE(...) Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MLTN_CORE_INFO(...) Log::GetCoreLogger()->info(__VA_ARGS__)
#define MLTN_CORE_WARN(...) Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MLTN_CORE_ERROR(...) Log::GetCoreLogger()->error(__VA_ARGS__)
#define MLTN_CORE_CRITICAL(...) Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MLTN_TRACE(...) Log::GetClientLogger()->trace(__VA_ARGS__)
#define MLTN_INFO(...) Log::GetClientLogger()->info(__VA_ARGS__)
#define MLTN_WARN(...) Log::GetClientLogger()->warn(__VA_ARGS__)
#define MLTN_ERROR(...) Log::GetClientLogger()->error(__VA_ARGS__)
#define MLTN_CRITICAL(...) Log::GetClientLogger()->critical(__VA_ARGS__)