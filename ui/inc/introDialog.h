#pragma once
#include "final/final.h"
#include "introLabel.h"
#include "iDialogChain.h"

using namespace finalcut;

class IntroDialog: public IDialogChain {
public:
    explicit IntroDialog(FDialog* parent);
    // void initLayout() override;
    void onTimer(FTimerEvent* event) override;
    void onKeyPress (FKeyEvent*) override;
    void onMouseDown(FMouseEvent* event) override;
private:
    void clearDialog();

    IntroLabel* introLabel;
    int introTimerId, pressKeyTimerId, barsTimerId;
};