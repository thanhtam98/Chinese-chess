#include "introDialog.h"
#include "mainDialog.h"
#include "log.h"

IntroDialog::IntroDialog(FDialog* parent): IDialogChain{parent} {
    setText("Intro Dialog");
    setGeometry(MAIN_DIALOG_POINT, WINDOW_SIZE, false);
    introTimerId = addTimer(200);
    pressKeyTimerId = addTimer(500);
    barsTimerId = addTimer(1500);
    introLabel = new IntroLabel{this};
}

void IntroDialog::onTimer(FTimerEvent* event) {
    if (event->getTimerId() == introTimerId) {
        introLabel->setColor();
    }
    if (event->getTimerId() == pressKeyTimerId) {
        introLabel->togglePressKey();
    }
    if (event->getTimerId() == barsTimerId) {
        introLabel->toggleBars();
    }
    redraw();
}

void IntroDialog::onKeyPress(FKeyEvent* event) {
    const auto key_id = event->key();
    auto key_name = finalcut::FVTerm::getFOutput()->getKeyName(key_id);
    LOG_F("Key %s", key_name.c_str())
    clearDialog();
}

void IntroDialog::onMouseDown(FMouseEvent* event) {
    clearDialog();
}

void IntroDialog::clearDialog() {
    delAllTimers();
    delCallback();
    close();
    next();
}