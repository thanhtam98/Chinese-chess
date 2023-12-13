#include "hostSelection.h"
#include "constant.h"

HostSelection::HostSelection(FDialog* parent) {
    buttonGroup = new FButtonGroup{HOST_SELECTION_LABEL, parent};
    buttonGroup->setGeometry (FPoint{2, 15}, FSize{41, 5});

    options.resize(2);
    FRadioButton* yesButton = new FRadioButton(YES, buttonGroup);
    yesButton->setGeometry(FPoint{4, 2}, FSize{10, 1});
    options[YES_OPTION] = yesButton;

    FRadioButton* noButton = new FRadioButton(NO, buttonGroup);
    noButton->setGeometry(FPoint{25, 2}, FSize{10, 1});
    options[NO_OPTION] = noButton;

    // Set you as a client by default
    options[NO_OPTION]->setChecked();
}

int HostSelection::select() {
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        if (buttonGroup->isChecked(n)) {
            return n - 1;
        }
    }
    return YES_OPTION;
}

void HostSelection::hide() {
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        buttonGroup->getButton(n)->hide();
    }
    buttonGroup->hide();
}

void HostSelection::show() {
    buttonGroup->show();
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        buttonGroup->getButton(n)->show();
    }
}

void HostSelection::setFocus() {
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        if (buttonGroup->isChecked(n)) {
            options[n-1]->setFocus();
            return;
        }
    }
    options[NO_OPTION]->setFocus();
}