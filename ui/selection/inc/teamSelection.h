#pragma once
#include "final/final.h"
#include <string>
#include <vector>
#include "radioButtonChain.h"

using namespace finalcut;

class TeamSelection: public RadioButtonChain {
public:
    static const int RED_OPTION = 0;
    static const int BLACK_OPTION = 1;

    explicit TeamSelection(FDialog* parent);

    int select() override;
    void setFocus() override;
private:
    const std::string TEAM_SELECTION_LABEL = "Please choose the team who goes first";
};