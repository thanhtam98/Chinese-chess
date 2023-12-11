#include "configDialog.h"
#include "mainDialog.h"
#include "teamSelection.h"

ConfigDialog::ConfigDialog(FDialog* parent): IDialogChain{parent} {
    setText("Configuration Dialog");
    setGeometry(MAIN_DIALOG_POINT, WINDOW_SIZE);
    modeSelection = new ModeSelection{this};
    TeamSelection* teamSelection = new TeamSelection{this};

    modeSelection->setNext(teamSelection, 0);
    modeSelection->setNext(teamSelection, 1);
    currentSelection = modeSelection;

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
    back.hide();
}

void ConfigDialog::okCallback() {
    int branch = currentSelection->select();
    if (currentSelection->hasNext(branch)) {
        currentSelection = (SelectableChain*) currentSelection->next(branch);
        if (currentSelection->hasBack()) {
            back.show();
        }
    } else {
        next();
    }
}

void ConfigDialog::backCallback() {
    currentSelection = (SelectableChain*) currentSelection->back();
    if (!currentSelection->hasBack()) {
        back.hide();
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