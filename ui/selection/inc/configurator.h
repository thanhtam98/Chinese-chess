#pragma once
#include <string>
#include <unordered_map>

enum param_t {
    MODE,
    TEAM,
    IP,
    HOST,
    PARAM_SIZE // Add new values above this line
};

class Configurator {
public:
    static std::string ONLINE;
    static std::string OFFLINE;
    static std::string DEBUG;
    static std::string RED;
    static std::string BLACK;

    static void set(param_t param, std::string value);
    static std::string get(param_t param);

    static void init();
private:
    static std::string properties[PARAM_SIZE];
};