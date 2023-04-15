#pragma once

#include "final/final.h"
#include "utils/constant.h"

using namespace finalcut;

class VerticleLineLabels {
public:
    explicit VerticleLineLabels(FWidget* parent);
private:
    FLabel* verticalLines[BOARD_WIDTH][BOARD_LENGTH-1];
    FLabel* verticalLinesAtBorder[2];
};