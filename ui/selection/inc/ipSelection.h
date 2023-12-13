#pragma once
#include "final/final.h"
#include "selectableChain.h"
#include <string>

using namespace finalcut;

class IpSelection: public SelectableChain {
public:
    explicit IpSelection(FDialog* parent);

    int select() override;
    void hide() override;
    void show() override;
    void setFocus() override;
private:
    const std::string IP_SELECTION_LABEL = "Server's IP address";
    const std::string INSTRUCTION = "Look at the table of IP addresses in the\nServer window and enter one of them here.\nA valid IP address should look like\nX.X.X.X, with X in the range of 0-255.";

    FLineEdit* ip;
    FLabel* instruction;
};