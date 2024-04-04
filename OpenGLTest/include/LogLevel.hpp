#pragma once

enum class LogLevel : short {
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERR,
    CRITCAL,
    OFF
};

inline spdlog::level::level_enum LogLevelToSpdlog(LogLevel logLevel) {
    switch (logLevel) {
    case LogLevel::TRACE:   return spdlog::level::trace;
    case LogLevel::DEBUG:   return spdlog::level::debug;
    case LogLevel::INFO:    return spdlog::level::info;
    case LogLevel::WARNING: return spdlog::level::warn;
    case LogLevel::ERR:     return spdlog::level::err;
    case LogLevel::CRITCAL: return spdlog::level::critical;
    case LogLevel::OFF:     return spdlog::level::off;
    default:                throw std::runtime_error("Log level convert error");
    }
}
