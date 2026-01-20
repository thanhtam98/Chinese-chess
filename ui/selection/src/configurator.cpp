#include "configurator.h"

std::string Configurator::ONLINE = "on";
std::string Configurator::OFFLINE = "of";
std::string Configurator::DEBUG = "d";
std::string Configurator::RED = "r";
std::string Configurator::BLACK = "b";
std::string Configurator::SERVER = "s";
std::string Configurator::CLIENT = "c";

std::string Configurator::properties[] = {};

void Configurator::set(param_t param, std::string value) {
    properties[param] = value;
}

std::string Configurator::get(param_t param) {
    return properties[param];
}

void Configurator::init() {
}