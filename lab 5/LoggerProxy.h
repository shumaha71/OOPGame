#pragma once
#include "Logger.h"
#include <ctime>
#include <sstream>

class LoggerProxy : public ILogger {
private:
    ILogger* realLogger;

    std::string getTimestamp() const {
        std::time_t now = std::time(nullptr);
        std::tm* localNow = std::localtime(&now);
        char buffer[32];
        std::strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S] ", localNow);
        return std::string(buffer);
    }

public:
    LoggerProxy(ILogger* realLogger) : realLogger(realLogger) {}

    void log(const std::string& message) override {
        std::string fullMessage = getTimestamp() + message;
        realLogger->log(fullMessage);
    }
};