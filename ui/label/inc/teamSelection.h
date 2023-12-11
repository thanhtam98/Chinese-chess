#pragma once
#include "final/final.h"
#include <string>
#include "selectableChain.h"

using namespace finalcut;

class TeamSelection: public SelectableChain {
public:
    explicit TeamSelection(FDialog* parent);

    int select() override;
    void hide() override;
    void show() override;
private:
    const std::string TEAM_SELECTION_LABEL = "Please choose the team who goes first";

    FButtonGroup* buttonGroup;
};