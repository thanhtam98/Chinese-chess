#ifndef __LOG_H__
#define __LOG_H__
#include <string>
#include <fstream>

#define LOGGER_FILE "session.log"
#define LOG(x) Logger::write(__LINE__, __FILE__, x)

class Logger {
public:
    static void write(int line, std::string fileName, std::string content);
    static Logger* getInstance();
    std::fstream file;
private:
    static Logger* instance;
};

#endif