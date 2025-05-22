#pragma once
#include "Logger.h"

// Адаптер, позволяющий использовать любой ILogger как логгер
class LoggerAdapter {
private:
    ILogger* logger;

public:
    LoggerAdapter(ILogger* logger) : logger(logger) {}

    void writeLog(const std::string& message) {
        logger->log(message);
    }
};