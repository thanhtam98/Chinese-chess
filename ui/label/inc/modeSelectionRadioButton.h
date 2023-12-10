#pragma once
#include "final/final.h"
#include <string>

using namespace finalcut;

class ModeSelectionRadioButton {
public:
    explicit ModeSelectionRadioButton(FDialog* parent);

    void selectMode();
    void addDebugTrick();
private:
    const std::string ONLINE = "Online"; 
    // const std::string ONLINE_DESC = "Each player on an individual computer.";
    const std::string OFFLINE = "Offline"; 
    // const std::string OFFLINE_DESC = "2 players on the same computer";
    const std::string DEBUG = "Debug"; 
    // const std::string DEBUG_DESC = "2 players moving freely withou turn\nrestriction";
    const std::string MODE_SELECTION_LABEL = "Please choose a mode";

    FButtonGroup* buttonGroup;
};