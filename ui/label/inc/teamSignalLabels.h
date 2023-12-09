#pragma once
#include "final/final.h"
#include "utils.h"

using namespace finalcut;

class TeamSignalLabels {
public:
    TeamSignalLabels(FWidget* parent);
    void changeTeamColor();
private:
    FColor getTeamBgColor(team_code team);

    FLabel* upper;
    FLabel* lower;
};