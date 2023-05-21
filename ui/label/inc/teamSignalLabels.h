#pragma once
#include "final/final.h"

using namespace finalcut;

class TeamSignalLabels {
public:
    TeamSignalLabels(FWidget* parent);
    void changeTeamColor();
private:
    FLabel* upper;
    FLabel* lower;
};