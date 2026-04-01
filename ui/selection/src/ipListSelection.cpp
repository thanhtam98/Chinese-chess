#include "ipListSelection.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "log.h"
#include <array>
#include "configurator.h"
#include "connectionBase.h"

std::vector<std::string> IpListSelection::LOCALHOST_NAMES = { "lo", "lo0" };

IpListSelection::IpListSelection(FDialog* parent, FButton* _okButton) {
    struct ifaddrs* ifAddrStruct = NULL;
    struct ifaddrs* ifa = NULL;

    okButton = _okButton;

    port = new FLineEdit{parent};
    port->setLabelText(ENTER_PORT_LABEL);
    port->setGeometry(FPoint{22, 18}, FSize{10, 1});
    port->front();
    port->getLabelObject()->front();
    port->setText("9000");

    ipList = new FListView{parent};
    ipList->addColumn("IP Address");
    ipList->addColumn("Name");
    ipList->setGeometry(FPoint{2, 10}, FSize{42, 5});

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        // Only accept IPv4
        if (ifa->ifa_addr->sa_family == AF_INET) {
            struct in_addr* tmpAddr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char *name = ifa->ifa_name;
            if (isLocalhost(std::string(name))) {
                continue;
            }
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddr, addressBuffer, INET_ADDRSTRLEN);
            LOG_F("Address: %s", addressBuffer);
            std::array<char *, INET_ADDRSTRLEN> address = { addressBuffer, name };
            FStringList content(address.cbegin(), address.cend());
            ipList->insert(content);
        }
        if (ifa->ifa_addr->sa_family == AF_INET6) {
            struct in6_addr* tmpAddr = &((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char *name = ifa->ifa_name;
            if (isLocalhost(std::string(name))) {
                continue;
            }
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddr, addressBuffer, INET6_ADDRSTRLEN);
            LOG_F("Address: %s", addressBuffer);
            std::array<char *, INET6_ADDRSTRLEN> address = { addressBuffer, name };
            FStringList content(address.cbegin(), address.cend());
            ipList->insert(content);
        }
    }
    // Hide all elements as default
    hide();
}

int IpListSelection::select() {
    const auto& item = ipList->getCurrentItem();
    Configurator::set(IP, item->getText(1).c_str());
    Configurator::set(PORT, port->getText().c_str());
    ConnectionBase::getInstance()->setPort(static_cast<uint16_t>(std::atoi(port->getText().c_str())));
    return 0;
}

void IpListSelection::hide() {
    ipList->hide();
    port->getLabelObject()->hide();
    port->hide();
}

void IpListSelection::show() {
    ipList->show();
    port->show();
    port->getLabelObject()->show();
}

void IpListSelection::setFocus() {
    ipList->setFocus();
}

bool IpListSelection::isLocalhost(std::string name) {
    for (auto localhost : LOCALHOST_NAMES) {
        if (localhost == name) {
            return true;
        }
    }
    return false;
}