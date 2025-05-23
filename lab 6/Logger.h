#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>

// Интерфейс логгера
class ILogger {
public:
    virtual void log(const std::string& message) = 0;
    virtual ~ILogger() = default;

    virtual void logBaseAction(const std::string& baseName, const std::string& action) {
        log("[Base] " + baseName + ": " + action);
    }

    virtual void logUnitAction(const std::string& unitType, const std::string& action) {
        log("[Unit] " + unitType + ": " + action);
    }

    virtual void logMapAction(const std::string& action) {
        log("[Map] " + action);
    }

    virtual void logSystem(const std::string& message) {
        log("[System] " + message);
    }
};

// Логгер в файл
class FileLogger : public ILogger {
    std::ofstream out;
public:
    FileLogger(const std::string& filename) {
        out.open(filename, std::ios::app);
    }

    void log(const std::string& message) override {
        if (out.is_open()) {
            out << message << std::endl;
        }
    }

    ~FileLogger() {
        if (out.is_open()) out.close();
    }
};

// Логгер в консоль
class ConsoleLogger : public ILogger {
public:
    void log(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

// Пустой логгер (ничего не делает)
class NoLogger : public ILogger {
public:
    void log(const std::string&) override {}
};

// Адаптер логгера
class LogAdapter {
    ILogger* logger;
public:
    LogAdapter(ILogger* logger) : logger(logger) {}

    ILogger* getLogger() const { return logger; }

    void logUnitAction(const std::string& unitType, const std::string& action) {
        logger->log("[Unit] " + unitType + ": " + action);
    }

    void logBaseAction(const std::string& baseName, const std::string& action) {
        logger->log("[Base] " + baseName + ": " + action);
    }

    void logMapAction(const std::string& action) {
        logger->log("[Map] " + action);
    }

    void logSystem(const std::string& message) {
        logger->log("[System] " + message);
    }
};

// Прокси-логгер
class LoggerProxy {
    LogAdapter* adapter = nullptr;
public:
    enum Mode { TO_FILE, TO_CONSOLE, DISABLED };

    LoggerProxy(Mode mode) {
        switch (mode) {
            case TO_FILE:
                adapter = new LogAdapter(new FileLogger("log.txt"));
                break;
            case TO_CONSOLE:
                adapter = new LogAdapter(new ConsoleLogger());
                break;
            case DISABLED:
                adapter = new LogAdapter(new NoLogger());
                break;
        }
    }

    LogAdapter* get() {
        return adapter;
    }

    ~LoggerProxy() {
        delete adapter;
    }
};

#endif // LOGGER_H

