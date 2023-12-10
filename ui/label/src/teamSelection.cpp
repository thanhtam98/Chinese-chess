#include "teamSelection.h"
#include "constant.h"
#include "ITurn.h"

TeamSelection::TeamSelection(FDialog* parent) {
    buttonGroup = new FButtonGroup(TEAM_SELECTION_LABEL, parent);
    buttonGroup->setGeometry (FPoint{2, 15}, FSize{41, 5});

    FRadioButton* redButton = new FRadioButton(RED_TEAM, buttonGroup);
    redButton->setGeometry(FPoint{4, 2}, FSize{10, 1});

    FRadioButton* blackButton = new FRadioButton(BLACK_TEAM, buttonGroup);
    blackButton->setGeometry(FPoint{25, 2}, FSize{10, 1});

    // Set Red as default
    redButton->setChecked();
    redButton->setFocus();
}

void TeamSelection::select() {
    turn_mode mode = ITurn::getMode();
    if (buttonGroup->isChecked(2) && mode == OFFLINE) {
        ITurn::newOfflineTurns(false);
    }
    if (buttonGroup->isChecked(2) && mode == ONLINE) {
        ITurn::newOnlineTurns(false);
    }
}

void TeamSelection::hide() {
    buttonGroup->hide();
}

void TeamSelection::show() {
    buttonGroup->show();
}