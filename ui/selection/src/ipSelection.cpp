#include "ipSelection.h"
#include "log.h"

IpSelection::IpSelection(FDialog* parent) {
    ip = new FLineEdit{parent};
    ip->setLabelText(IP_SELECTION_LABEL);
    ip->setGeometry(FPoint{22, 18}, FSize{20, 1});
    ip->front();
    ip->getLabelObject()->front();
    
    instruction = new FLabel{parent};
    instruction->setText(INSTRUCTION);
    instruction->setGeometry(FPoint{4, 12}, FSize{41, 4});
    // instruction->setBackgroundColor(FColor::Grey50);
    instruction->setForegroundColor(FColor::Grey84);
}

int IpSelection::select() {
    
    LOG_F("Enter: %s", ip->getText().c_str());
    return 0;
}

void IpSelection::hide() {
    ip->getLabelObject()->hide();
    ip->hide();
    instruction->hide();
}

void IpSelection::show() {
    ip->show();
    ip->getLabelObject()->show();
    instruction->show();
}

void IpSelection::setFocus() {
    ip->setFocus();
}