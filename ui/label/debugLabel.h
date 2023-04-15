#pragma once

#include "final/final.h"
#include "utils/constant.h"
#include <string>

using namespace finalcut;

class DebugLabel {
public:
    explicit DebugLabel(FWidget* parent);
    void log(std::string content);
private:
    FLabel* debug;
};