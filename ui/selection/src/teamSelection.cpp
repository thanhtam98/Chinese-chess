#include "teamSelection.h"
#include "constant.h"
#include "configurator.h"

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
    // Hide all elements as default
    hide();
}

int TeamSelection::select() {
    if (buttonGroup->isChecked(RED_OPTION+1)) {
        Configurator::set(TEAM, Configurator::RED);
    }
    if (buttonGroup->isChecked(BLACK_OPTION+1)) {
        Configurator::set(TEAM, Configurator::BLACK);
    }
    return 0;
}

void TeamSelection::setFocus() {
    options[RED_OPTION]->setFocus();
    RadioButtonChain::setFocus();
}