#pragma once
#include "final/final.h"
#include "radioButtonChain.h"
#include <string>
#include <vector>

using namespace finalcut;

class HostSelection: public RadioButtonChain {
public:
    static const int YES_OPTION = 0;
    static const int NO_OPTION = 1;

    explicit HostSelection(FDialog* parent);

    int select() override;
    void setFocus() override;
    
private:
    const std::string HOST_SELECTION_LABEL = "Do you want to host the game?";
};