#include "modeSelection.h"
#include <memory>
#include "log.h"
#include "ITurn.h"

using namespace std;

ModeSelection::ModeSelection(FDialog* parent) {
    buttonGroup = new FButtonGroup(MODE_SELECTION_LABEL, parent);
    buttonGroup->setGeometry (FPoint{2, 15}, FSize{41, 5});

    options.resize(2);
    options[ONLINE_OPTION] = new FRadioButton(ONLINE, buttonGroup);
    options[ONLINE_OPTION]->setGeometry(FPoint{4, 2}, FSize{10, 1});

    options[OFFLINE_OPTION] = new FRadioButton(OFFLINE, buttonGroup);
    options[OFFLINE_OPTION]->setGeometry(FPoint{25, 2}, FSize{10, 1});

    // Temporarily set OFFLINE as default
    options[OFFLINE_OPTION]->setChecked();
    options[OFFLINE_OPTION]->setFocus();
}

void ModeSelection::addDebugTrick() {
    options.resize(3);
    FRadioButton *debugButton = new FRadioButton(DEBUG, buttonGroup);
    debugButton->setGeometry(FPoint{4, 3}, FSize{10, 1});
    debugButton->back();
    debugButton->setChecked();
    options[DEBUG_OPTION] = debugButton;
    // debugButton->setFocus();
    // debugButton->front();
}

int ModeSelection::select(){
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        if (buttonGroup->isChecked(n)) {
            FString mode = buttonGroup->getButton(n)->getText();
            LOG_F("Select: %s", mode.c_str());
            if (mode == DEBUG) {
                ITurn::newDebugTurns();
                return DEBUG_OPTION;
            }
            if (mode == OFFLINE) {
                ITurn::newOfflineTurns();
                return OFFLINE_OPTION;
            }
            if (mode == ONLINE) {
                ITurn::newOnlineTurns();
                return ONLINE_OPTION;
            }
        }
    }
    return ONLINE_OPTION;
}

void ModeSelection::setFocus() {
    options[OFFLINE_OPTION]->setFocus();
    RadioButtonChain::setFocus();
}