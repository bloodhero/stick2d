#include "pch.h"

#include "Core/Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/null_sink.h>

namespace stick2d {

    Logger::Logger()
    {
        std::array<spdlog::sink_ptr, 2> log_sinks;
        log_sinks[0] = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        log_sinks[1] = std::make_shared<spdlog::sinks::basic_file_sink_mt>("stick2d.log", true);

        log_sinks[0]->set_pattern("%^[%T] [%l]: %v%$");
        log_sinks[1]->set_pattern("[%T] [%l]: %v");

        auto engine_logger = std::make_shared<spdlog::logger>("engine_logger", begin(log_sinks), end(log_sinks));

#ifdef _DEBUG
        engine_logger->set_level(spdlog::level::trace);
#else
        engine_logger->set_level(spdlog::level::info);
#endif

        engine_logger->flush_on(spdlog::level::trace);
        spdlog::register_logger(engine_logger);

        spdlog::create<spdlog::sinks::null_sink_st>("null_logger");

        spdlog::set_default_logger(engine_logger);

        LOG_TRACE("Logger is initialized.");
    }

    Logger::~Logger()
    {
        LOG_TRACE("Logger is closed.");

        spdlog::drop_all();
    }

    void Logger::enableLog()
    {
        spdlog::set_default_logger(spdlog::get("engine_logger"));
    }

    void Logger::disableLog()
    {
        spdlog::set_default_logger(spdlog::get("null_logger"));
    }


    Logger* theLogger()
    {
        static Logger instance;
        return &instance;
    }

}