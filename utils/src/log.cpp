#include "log.h"
#include <iostream>
#include <stdio.h>

using namespace::std;

Logger* Logger::instance = nullptr;
std::string Logger::logFilePath = LOGGER_FILE;

void Logger::setLogFilePath(const std::string& path) {
    if (path.empty()) {
        logFilePath = LOGGER_FILE;
        return;
    }
    logFilePath = path;
}

const std::string& Logger::getLogFilePath() {
    return logFilePath;
}

Logger* Logger::getInstance() {
    if (instance == nullptr) {
        remove(logFilePath.c_str());
        instance = new Logger();
    }
    return instance;
}

void Logger::write(int line, std::string fileName, std::string content) {
    Logger* logger = getInstance();
    logger->file.open(logFilePath, ios::out | ios::app);

    if (logger->file) {
        logger->file << "[" << fileName << ":" <<
            line << "] --- " << content << endl;
    } else {
        logger->file << "Cannot open file" << endl;
    }
    logger->file.close();
}

Logger& operator<<(Logger &logger, std::string content) {
    logger.file.open(Logger::getLogFilePath(), ios::out | ios::app);

    if (logger.file) {
        logger.file << content << endl;
    } else {
        logger.file << "Cannot open file" << endl;
    }
    logger.file.close();
    return logger;
}

Logger& operator<<(Logger &logger, int content) {
    logger.file.open(Logger::getLogFilePath(), ios::out | ios::app);

    if (logger.file) {
        logger.file << content << endl;
    } else {
        logger.file << "Cannot open file" << endl;
    }
    logger.file.close();
    return logger;
}
