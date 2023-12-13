#include "teamSelection.h"
#include "constant.h"
#include "ITurn.h"

TeamSelection::TeamSelection(FDialog* parent) {
    buttonGroup = new FButtonGroup(TEAM_SELECTION_LABEL, parent);
    buttonGroup->setGeometry (FPoint{2, 15}, FSize{41, 5});

    options.resize(2);
    FRadioButton* redButton = new FRadioButton(RED_TEAM, buttonGroup);
    redButton->setGeometry(FPoint{4, 2}, FSize{10, 1});
    options[RED_OPTION] = redButton;

    FRadioButton* blackButton = new FRadioButton(BLACK_TEAM, buttonGroup);
    blackButton->setGeometry(FPoint{25, 2}, FSize{10, 1});
    options[BLACK_OPTION] = blackButton;

    // Set Red as default
    redButton->setChecked();
}

int TeamSelection::select() {
    turn_mode mode = ITurn::getMode();
    if (buttonGroup->isChecked(BLACK_OPTION+1) && mode == OFFLINE) {
        ITurn::newOfflineTurns(false);
        return BLACK_OPTION;
    }
    if (buttonGroup->isChecked(BLACK_OPTION+1) && mode == ONLINE) {
        ITurn::newOnlineTurns(false);
        return BLACK_OPTION;
    }
    return 0;
}

void TeamSelection::hide() {
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        buttonGroup->getButton(n)->hide();
    }
    buttonGroup->hide();
}

void TeamSelection::show() {
    buttonGroup->show();
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        buttonGroup->getButton(n)->show();
    }
}

void TeamSelection::setFocus() {
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        if (buttonGroup->isChecked(n)) {
            options[n-1]->setFocus();
            return;
        }
    }
    options[RED_OPTION]->setFocus();
}