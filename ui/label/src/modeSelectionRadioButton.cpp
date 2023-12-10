#include "modeSelectionRadioButton.h"
#include <memory>
#include <vector>
#include "log.h"
#include "ITurn.h"

using namespace std;
// using FRadioButtonPtr = shared_ptr<FRadioButton>;

ModeSelectionRadioButton::ModeSelectionRadioButton(FDialog* parent) {
    buttonGroup = new FButtonGroup(MODE_SELECTION_LABEL, parent);
    buttonGroup->setGeometry (FPoint{2, 15}, FSize{41, 5});

    vector<FRadioButton *> options(3);
    options[0] = new FRadioButton(ONLINE, buttonGroup);
    options[0]->setGeometry(FPoint{4, 2}, FSize{10, 1});

    options[1] = new FRadioButton(OFFLINE, buttonGroup);
    options[1]->setGeometry(FPoint{25, 2}, FSize{10, 1});

    // Temporarily set DEBUG as default
    options[1]->setChecked();
    options[1]->setFocus();
}

void ModeSelectionRadioButton::addDebugTrick() {
    FRadioButton *debugButton = new FRadioButton(DEBUG, buttonGroup);
    debugButton->setGeometry(FPoint{4, 3}, FSize{10, 1});
    debugButton->setChecked();
    debugButton->setFocus();
    debugButton->front();
}

void ModeSelectionRadioButton::selectMode(){
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        if (buttonGroup->isChecked(n)) {
            FString mode = buttonGroup->getButton(n)->getText();
            LOG_F("Select: %s", mode.c_str());
            if (mode == DEBUG) {
                ITurn::newDebugTurns();
            }
            if (mode == OFFLINE) {
                ITurn::newOfflineTurns();
            }
            if (mode == ONLINE) {
                ITurn::newOnlineTurns();
            }
        }
    }
}