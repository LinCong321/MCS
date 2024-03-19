#include "logger.h"

namespace mcs {
    std::string logLevelToStr(LogLevel logLevel) {
        switch (logLevel) {
            case LogLevel::ERROR:
                return "[ERROR]";
            case LogLevel::WARNING:
                return "[ WARN]";
            case LogLevel::INFO:
                return "[ INFO]";
            default:
                return "UNKNOWN";
        }
    }

    std::string timeToStr() {
        const auto now = std::chrono::system_clock::now();
        const auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << '[' << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << ']';
        return ss.str();
    }

    std::string fileToStr(const std::string& file) {
        return std::string("[") + file.substr(file.find("MCS")) + ']';
    }
}