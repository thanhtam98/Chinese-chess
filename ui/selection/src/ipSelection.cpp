#include "ipSelection.h"
#include "log.h"
#include "configurator.h"
#include "connectionBase.h"

IpSelection::IpSelection(FDialog* parent) {
    ip = new FLineEdit{parent};
    ip->setLabelText(IP_SELECTION_LABEL);
    ip->setGeometry(FPoint{22, 16}, FSize{22, 1});
    ip->front();
    ip->getLabelObject()->front();
    ip->setText("127.0.0.1");

    port = new FLineEdit{parent};
    port->setLabelText(ENTER_PORT_LABEL);
    port->setGeometry(FPoint{22, 18}, FSize{10, 1});
    port->front();
    port->getLabelObject()->front();
    port->setText("9000");
    
    instruction = new FLabel{parent};
    instruction->setText(INSTRUCTION);
    instruction->setGeometry(FPoint{4, 6}, FSize{41, 4});
    // instruction->setBackgroundColor(FColor::Grey50);
    instruction->setForegroundColor(FColor::Grey84);
    // Hide all elements as default
    hide();
}

int IpSelection::select() {
    Configurator::set(IP, ip->getText().c_str());
    Configurator::set(PORT, port->getText().c_str());
    ConnectionBase::getInstance()->setPort(static_cast<uint16_t>(std::atoi(port->getText().c_str())));
    ConnectionBase::getInstance()->setHost(ip->getText().c_str());
    LOG_F("Enter: %s", ip->getText().c_str());
    return 0;
}

void IpSelection::hide() {
    ip->getLabelObject()->hide();
    ip->hide();
    port->getLabelObject()->hide();
    port->hide();
    instruction->hide();
}

void IpSelection::show() {
    ip->show();
    ip->getLabelObject()->show();
    port->show();
    port->getLabelObject()->show();
    instruction->show();
}

void IpSelection::setFocus() {
    ip->setFocus();
}