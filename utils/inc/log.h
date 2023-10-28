#ifndef __LOG_H__
#define __LOG_H__
#include <string>
#include <fstream>

#define LOGGER_FILE "session.log"
#define LOG (*Logger::getInstance())<<"[]"<<__FILE__<<":"<<__LINE__<<" --- "
#define LOG_F(x) Logger::write(__LINE__, __FILE__, x)

class Logger {
public:
    static void write(int line, std::string fileName, std::string content);
    friend Logger& operator<<(Logger &logger, std::string content);
    friend Logger& operator<<(Logger &logger, int content);
    static Logger* getInstance();
    std::fstream file;
private:
    static Logger* instance;
};

#endif