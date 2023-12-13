#include "radioButtonChain.h"

void RadioButtonChain::hide() {
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        buttonGroup->getButton(n)->hide();
    }
    buttonGroup->hide();
}

void RadioButtonChain::show() {
    buttonGroup->show();
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        buttonGroup->getButton(n)->show();
    }
}

void RadioButtonChain::setFocus() {
    for (auto n = 1; n <= int(buttonGroup->getCount()); n++) {
        if (buttonGroup->isChecked(n)) {
            options[n-1]->setFocus();
            return;
        }
    }
}