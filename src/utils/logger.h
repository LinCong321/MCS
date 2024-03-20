#pragma once

#include <iostream>

namespace mcs {
    enum class LogLevel : uint {
        ERROR = 1,
        WARNING = 2,
        INFO = 3,
    };

    std::string logLevelToStr(LogLevel logLevel);

    std::string timeToStr();

    std::string fileToStr(const std::string& file);

    template <class... Args>
    void logger(LogLevel level, const char* file, const char* function, const Args&... args) {
        std::cout << logLevelToStr(level) << timeToStr() << fileToStr(file) << '[' << function << "()]: ";
        ((std::cout << args), ...);
        std::cout << std::endl;
    }
}

#define LOG_ERROR(...)  logger(mcs::LogLevel::ERROR, __FILE__, __FUNCTION__,  __VA_ARGS__)
#define LOG_WARN(...)   logger(mcs::LogLevel::WARNING, __FILE__, __FUNCTION__,  __VA_ARGS__)
#define LOG_INFO(...)   logger(mcs::LogLevel::INFO, __FILE__, __FUNCTION__,  __VA_ARGS__)