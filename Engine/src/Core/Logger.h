#pragma once

#include <SDL.h>

#include <spdlog/spdlog.h>
#include <memory>

namespace stick2d {

    class Logger
    {
    public:
        void enableLog();
        void disableLog();
    private:
        Logger();
        ~Logger();

        friend Logger* theLogger();
    };

}

// General log macros
#define LOG_TRACE(...)    spdlog::trace(__VA_ARGS__)
#define LOG_INFO(...)     spdlog::info(__VA_ARGS__)
#define LOG_WARN(...)     spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...)    spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

// Renderer log macros
#define LOG_RENDERER_TRACE(...)    spdlog::trace("[renderer] " __VA_ARGS__)
#define LOG_RENDERER_INFO(...)     spdlog::info("[renderer] " __VA_ARGS__)
#define LOG_RENDERER_WARN(...)     spdlog::warn("[renderer] " __VA_ARGS__)
#define LOG_RENDERER_ERROR(...)    spdlog::error("[renderer] " __VA_ARGS__)
#define LOG_RENDERER_CRITICAL(...) spdlog::critical("[renderer] " __VA_ARGS__)

// Audio log macros
#define LOG_AUDIO_TRACE(...)    spdlog::trace("[audio] " __VA_ARGS__)
#define LOG_AUDIO_INFO(...)     spdlog::info("[audio] " __VA_ARGS__)
#define LOG_AUDIO_WARN(...)     spdlog::warn("[audio] " __VA_ARGS__)
#define LOG_AUDIO_ERROR(...)    spdlog::error("[audio] " __VA_ARGS__)
#define LOG_AUDIO_CRITICAL(...) spdlog::critical("[audio] " __VA_ARGS__)

#ifdef _DEBUG
#define DEBUGBREAK()         __debugbreak()
#define ASSERT(x, ...) { if(!(x)) { LOG_ERROR(__VA_ARGS__); DEBUGBREAK(); } }
#else
#define DEBUGBREAK()
#define ASSERT(x, ...)
#endif