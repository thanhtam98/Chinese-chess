#pragma once
#include "final/final.h"
#include <string>
#include <vector>
#include "radioButtonChain.h"

using namespace finalcut;

class ModeSelection: public RadioButtonChain {
public:
    static const int ONLINE_OPTION = 0;
    static const int OFFLINE_OPTION = 1;
    static const int DEBUG_OPTION = 2;

    explicit ModeSelection(FDialog* parent);

    int select() override;
    void setFocus() override;
    void addDebugTrick();
private:
    const std::string ONLINE = "Online"; 
    // const std::string ONLINE_DESC = "Each player on an individual computer.";
    const std::string OFFLINE = "Offline"; 
    // const std::string OFFLINE_DESC = "2 players on the same computer";
    const std::string DEBUG = "Debug"; 
    // const std::string DEBUG_DESC = "2 players moving freely withou turn\nrestriction";
    const std::string MODE_SELECTION_LABEL = "Please choose a mode";
};