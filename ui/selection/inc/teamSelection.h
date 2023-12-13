#pragma once
#include "final/final.h"
#include <string>
#include <vector>
#include "selectableChain.h"

using namespace finalcut;

class TeamSelection: public SelectableChain {
public:
    static const int RED_OPTION = 0;
    static const int BLACK_OPTION = 1;

    explicit TeamSelection(FDialog* parent);

    int select() override;
    void hide() override;
    void show() override;
    void setFocus() override;
private:
    const std::string TEAM_SELECTION_LABEL = "Please choose the team who goes first";

    FButtonGroup* buttonGroup;
    std::vector<FRadioButton *> options;
};