#pragma once

#include "final/final.h"
#include "constant.h"

using namespace finalcut;

class HorizontalLineLabels {
public:
    explicit HorizontalLineLabels(FWidget* parent);
private:
    FLabel* horizontalLines[BOARD_WIDTH-1][BOARD_LENGTH];
};