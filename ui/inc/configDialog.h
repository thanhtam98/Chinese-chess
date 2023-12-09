#pragma once
#include "final/final.h"
#include "modeSelectionRadioButton.h"
#include "iChain.h"

using namespace finalcut;

class ConfigDialog: public FDialog, public IChain {
public:
    explicit ConfigDialog(FDialog* parent);
    void selectMode();
    void onKeyPress (FKeyEvent*) override;
private:

    ModeSelectionRadioButton* modeRadio;
    FButton ok{"&OK", this};
    FButton back{"&Back", this};
};
