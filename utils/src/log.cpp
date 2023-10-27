#include "log.h"
#include <iostream>
#include <stdio.h>

using namespace::std;

Logger* Logger::instance = nullptr;
Logger* Logger::getInstance() {
    if (instance == nullptr) {
        remove(LOGGER_FILE);
        instance = new Logger();
    }
    return instance;
}

void Logger::write(int line, std::string fileName, std::string content) {
    Logger* logger = getInstance();
    logger->file.open(LOGGER_FILE, ios::out | ios::app);

    if (logger->file) {
        logger->file << "[" << fileName << ":" <<
            line << "] --- " << content << endl;
    } else {
        logger->file << "Cannot open file" << endl;
    }
    logger->file.close();
}

Logger* operator<<(Logger* &logger, std::string content) {
    logger->file.open(LOGGER_FILE, ios::out | ios::app);

    if (logger->file) {
        logger->file << content << endl;
    } else {
        logger->file << "Cannot open file" << endl;
    }
    logger->file.close();
}