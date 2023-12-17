#pragma once
#include "final/final.h"
#include <string>
#include <vector>
#include "radioButtonChain.h"
#include "boardDialog.h"

using namespace finalcut;

class ModeSelection: public RadioButtonChain {
public:
    static const int ONLINE_OPTION = 0;
    static const int OFFLINE_OPTION = 1;
    static const int DEBUG_OPTION = 2;

    explicit ModeSelection(FDialog* parent);

    int select() override;
    void setFocus() override;
    void hide() override;
    void show() override;
    void initHook() override;
    void addDebugTrick();
    void onTimer(FTimerEvent* event);
private:
    const int DECORATOR_LENGTH = 2;
    const int DECORATOR_WIDTH = 5;
    const int INTERVAL = 1000;
    void addHighlight(FTextView* view, FTextView::FTextHighlight &highlight, int end = 2);

    const std::string ONLINE = "Online"; 
    const std::string ONLINE_DESC = "Each player on each\ncomputer connected\non the same LAN.";
    const std::string OFFLINE = "Offline"; 
    const std::string OFFLINE_DESC = "2 players on the\nsame computer.";
    const std::string DEBUG = "Debug"; 
    // const std::string DEBUG_DESC = "2 players moving freely without turn\nrestriction";
    const std::string MODE_SELECTION_LABEL = "Please choose a mode";

    int turnTimerId;
    FDialog* _parent;

    FTextView *one, *two, *both;
    FTextView::FTextHighlight red{0, (size_t)DECORATOR_WIDTH, RED_BG}, black{0, (size_t)DECORATOR_WIDTH, BLACK_BG}, noTeam{0, (size_t)DECORATOR_WIDTH, NOTEAM_BG};
    FLabel* divider, *connector, *online, *offline;
    FTextView *onlineDesc, *offlineDesc;
};