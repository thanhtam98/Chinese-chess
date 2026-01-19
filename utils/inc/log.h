#ifndef __LOG_H__
#define __LOG_H__
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdarg>

#define LOGGER_FILE "session.log"
#define LOG (*Logger::getInstance())<<"[]"<<__FILE__<<":"<<__LINE__<<" --- "
#define LOG_F(x,...) { \
    char buff[MAX_BUFF]; \
    sprintf(buff, x __VA_OPT__(,) __VA_ARGS__); \
    Logger::write(__LINE__, __FILE__, std::string(buff)); \
}
#define MAX_BUFF 100

class Logger {
public:
    static char buff[MAX_BUFF];
    static void write(int line, std::string fileName, std::string content);
    static void setLogFilePath(const std::string& path);
    static const std::string& getLogFilePath();
    friend Logger& operator<<(Logger &logger, std::string content);
    friend Logger& operator<<(Logger &logger, int content);
    static Logger* getInstance();
    std::fstream file;
private:
    static std::string logFilePath;
    static Logger* instance;
};

#endif
