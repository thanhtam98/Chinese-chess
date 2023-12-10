#include "configDialog.h"
#include "mainDialog.h"

ConfigDialog::ConfigDialog(FDialog* parent): IDialogChain{parent} {
    setText("Configuration Dialog");
    setGeometry(MAIN_DIALOG_POINT, WINDOW_SIZE);
    modeSelection = new ModeSelection{this};

    ok.front();
    ok.setGeometry(FPoint{34, 20}, FSize{8, 1});
    ok.addCallback(
        "clicked",
        this,
        &ConfigDialog::okCallback
    );

    back.front();
    back.setGeometry(FPoint{24, 20}, FSize{8, 1});
    back.addCallback(
        "clicked",
        this,
        &ConfigDialog::backCallback
    );
    back.setDisable();

    currentSelection = modeSelection;
}

void ConfigDialog::okCallback() {
    currentSelection->select();
    if (currentSelection->hasNext()) {
        currentSelection = (SelectableChain*) currentSelection->next();
        if (currentSelection->hasBack()) {
            back.setEnable();
        }
    } else {
        next();
    }
}

void ConfigDialog::backCallback() {
    if (currentSelection->hasBack()) {
        currentSelection->back();
    } else {
        back.setDisable();
    }
}

void ConfigDialog::onKeyPress(FKeyEvent* event) {
    const auto key_id = event->key();
    auto key_name = finalcut::FVTerm::getFOutput()->getKeyName(key_id);
    LOG_F("Key %s", key_name.c_str());
    if (key_name == "d" || key_name == "D") {
        modeSelection->addDebugTrick();
        // redraw();
    }
}