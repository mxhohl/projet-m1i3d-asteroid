#ifndef PROJETPROGAVANCEE_LOGGER_HPP
#define PROJETPROGAVANCEE_LOGGER_HPP

#include <string>
#include <unordered_map>
#include <fstream>

class Logger {
public:
    enum Level {
        FATAL = 0,
        ERROR = 1,
        WARN  = 2,
        INFO  = 3,
        DEBUG = 4
    };

    static inline std::string toString(Level level) {
        switch (level) {
            case FATAL:
                return "FATAL";
            case ERROR:
                return "ERROR";
            case WARN:
                return " WARN";
            case INFO:
                return " INFO";
            case DEBUG:
                return "DEBUG";
        }
        return "?????";
    }

    enum Options : unsigned {
        TERMINAL = 1u << 0u,
        FILE     = 1u << 1u,
        WINDOW   = 1u << 2u,
        ABORT    = 1u << 3u
    };

private:
    Logger();

public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

public:
    void setDisplayOptions(Level level, Options newOptions);

    Level getLogLevel() const;
    void setLogLevel(Level level);

    void fatal(const char* funcName, const std::string& message);
    void error(const char* funcName, const std::string& message);
    void warn(const char* funcName, const std::string& message);
    void info(const char* funcName, const std::string& message);
    void debug(const char* funcName, const std::string& message);

    void log(Level level, const std::string& funcName,
             const std::string& message);

private:
    void displayInTerminal(Level level, const std::string& funcName,
                           const std::string& message);
    void displayInFile(Level level, const std::string& funcName,
                       const std::string& message);
    void displayMessageBox(Level level, const std::string& funcName,
                           const std::string& message);

    void openLogFile();

private:
    Level logLevel;
    std::unordered_map<Level, Options> options;
    std::ofstream logFile;

};

#define FATAL(...) Logger::getInstance().fatal(__FUNCTION__, __VA_ARGS__)
#define ERROR(...) Logger::getInstance().error(__FUNCTION__, __VA_ARGS__)
#define WARN(...) Logger::getInstance().warn(__FUNCTION__, __VA_ARGS__)
#define INFO(...) Logger::getInstance().info(__FUNCTION__, __VA_ARGS__)
#define DEBUG(...) Logger::getInstance().debug(__FUNCTION__, __VA_ARGS__)

#endif //PROJETPROGAVANCEE_LOGGER_HPP
