#pragma once

#include <spdlog/spdlog.h>
#include <memory>

namespace stick2d {

    class Logger
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

}

// Core log macros
#define LOG_CORE_TRACE(...)    ::stick2d::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)     ::stick2d::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)     ::stick2d::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)    ::stick2d::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...) ::stick2d::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define LOG_TRACE(...)         ::stick2d::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)          ::stick2d::Logger::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          ::stick2d::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         ::stick2d::Logger::GetClientLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      ::stick2d::Logger::GetClientLogger()->critical(__VA_ARGS__)