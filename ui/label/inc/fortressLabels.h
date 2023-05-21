#pragma once

#include "final/final.h"

using namespace finalcut;

class FortressLabels {
public:
    explicit FortressLabels(FWidget* parent);
private:
    FLabel* fortressLines[2][4];
};