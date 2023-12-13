#pragma once
#include "final/final.h"
#include "selectableChain.h"
#include <vector>
#include <string>

using namespace finalcut;

class IpListSelection: public SelectableChain {
public:
    static const int DONE = 0;
    static const int TIMEOUTED = 1;
    static std::vector<std::string> LOCALHOST_NAMES;

    explicit IpListSelection(FDialog* parent);

    int select() override;
    void hide() override;
    void show() override;
    void setFocus() override;
private:
    bool isLocalhost(std::string name);

    FListView* ipList;
};