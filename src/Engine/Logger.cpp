#include <iostream>
#include <chrono>
#include <SDL_messagebox.h>
#include <sys/stat.h>

#include "Engine/Logger.hpp"
#include "Engine/Utils.hpp"

using namespace engine;

Logger::Logger() :
        logLevel(INFO),
        options{
            {FATAL, Options(TERMINAL | FILE | WINDOW | ABORT)},
            {ERROR, Options(TERMINAL | FILE | WINDOW)},
            {WARN,  Options(TERMINAL | FILE)},
            {INFO,  Options(TERMINAL | FILE)},
            {DEBUG, Options(TERMINAL | FILE)}
        } {
    openLogFile();
}

void Logger::setDisplayOptions(Level level, Options newOptions) {
    options[level] = newOptions;
}

Logger::Level Logger::getLogLevel() const {
    return logLevel;
}

void Logger::setLogLevel(Logger::Level level) {
    logLevel = level;
}

void Logger::fatal(const char* funcName, const std::string &message) {
    log(FATAL, funcName, message);
}

void Logger::error(const char *funcName, const std::string &message) {
    log(ERROR, funcName, message);
}

void Logger::warn(const char *funcName, const std::string &message) {
    log(WARN, funcName, message);
}

void Logger::info(const char *funcName, const std::string &message) {
    log(INFO, funcName, message);
}

void Logger::debug(const char *funcName, const std::string &message) {
    log(DEBUG, funcName, message);
}

void Logger::log(Level level, const std::string &funcName,
                 const std::string &message) {
    const auto levelOptions = options[level];

    if (levelOptions & TERMINAL) {
        displayInTerminal(level, funcName, message);
    }
    if (levelOptions & FILE) {
        displayInFile(level, funcName, message);
    }
    if (levelOptions & WINDOW) {
        displayMessageBox(level, funcName, message);
    }
    if (levelOptions & ABORT) {
        abort();
    }
}

void Logger::displayInTerminal(Level level, const std::string& funcName,
                               const std::string &message) {
    std::cerr << ::toString(std::chrono::system_clock::now())
              << " [" << toString(level) << "] ["
              << funcName << "] "
              << message
              << std::endl;
}

void Logger::displayInFile(Level level, const std::string &funcName,
                           const std::string &message) {
    logFile << ::toString(std::chrono::system_clock::now())
            << " [" << toString(level) << "] ["
            << funcName << "] "
            << message
            << std::endl;
}

void Logger::displayMessageBox(Level level, const std::string& funcName,
                               const std::string& message) {
    if (level > logLevel) {
        return;
    }

    Uint32 flag;
    switch (level) {
        case FATAL:
        case ERROR:
            flag = SDL_MESSAGEBOX_ERROR;
            break;
        case WARN:
            flag = SDL_MESSAGEBOX_WARNING;
            break;
        case INFO:
        case DEBUG:
            flag = SDL_MESSAGEBOX_INFORMATION;
            break;
    }

    SDL_ShowSimpleMessageBox(
            flag,
            toString(level).c_str(),
            (funcName + ": \n" + message).c_str(),
            nullptr
    );
}

void Logger::openLogFile() {
    const std::string baseFileName = ::toString(
            std::chrono::system_clock::now(),
            "%Y-%m-%d-"
    );

    int nb = 1;
    std::string fileName = sstr(baseFileName, nb, ".log");

    while (fileExists(fileName)) {
        ++nb;
        fileName = sstr(baseFileName, nb, ".log");
    }

    logFile.open(fileName, std::ios::out | std::ios::app);

    if (!logFile.good()) {
        displayInTerminal(FATAL, __FUNCTION__, "Unable to open log file");
        displayMessageBox(FATAL, __FUNCTION__, "Unable to open log file");
        throw std::runtime_error("Unable to open log file");
    }
}
