#pragma once
#include "final/final.h"
#include "modeSelection.h"
#include "iDialogChain.h"
#include "selectableChain.h"
#include "waitableChain.h"

using namespace finalcut;

#define DESC_COLOR FColor::Grey50

class ConfigDialog: public IDialogChain {
public:
    explicit ConfigDialog(FDialog* parent);
    void okCallback();
    void backCallback();
    void onKeyPress (FKeyEvent*) override;
    void onTimer(FTimerEvent* event) override;

    inline void initHook() override;
private:
    FButton ok{"Next &>", this};
    FButton back{"&< Back", this};
    SelectableChain* currentSelection;
    ModeSelection* modeSelection;
    // WaitableChain* serverWaitableChain;
    // WaitableChain* clientWaitableChain;
};
