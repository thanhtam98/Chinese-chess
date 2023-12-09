#include "configDialog.h"
#include "mainDialog.h"

ConfigDialog::ConfigDialog(FDialog* parent): FDialog{parent} {
    setGeometry(MAIN_DIALOG_POINT, WINDOW_SIZE, false);
    modeRadio = new ModeSelectionRadioButton{this};

    ok.front();
    ok.setGeometry(FPoint{34, 20}, FSize{8, 1});
    ok.addCallback(
        "clicked",
        this,
        &ConfigDialog::selectMode
    );

    back.front();
    back.setGeometry(FPoint{24, 20}, FSize{8, 1});
}

void ConfigDialog::selectMode() {
    modeRadio->selectMode();
}

void ConfigDialog::onKeyPress(FKeyEvent* event) {
    const auto key_id = event->key();
    auto key_name = finalcut::FVTerm::getFOutput()->getKeyName(key_id);
    LOG_F("Key %s", key_name.c_str());
    if (key_name == "d" || key_name == "D") {
        modeRadio->addDebugTrick();
        // redraw();
    }
}