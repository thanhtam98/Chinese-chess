#pragma once
#include "final/final.h"
#include "modeSelection.h"
#include "iDialogChain.h"
#include "selectableChain.h"

using namespace finalcut;

class ConfigDialog: public IDialogChain {
public:
    explicit ConfigDialog(FDialog* parent);
    void okCallback();
    void backCallback();
    void onKeyPress (FKeyEvent*) override;
private:
    SelectableChain* currentSelection;
    ModeSelection* modeSelection;
    FButton ok{"Next &>", this};
    FButton back{"&< Back", this};
};
