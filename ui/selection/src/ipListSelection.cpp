#include "ipListSelection.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "log.h"
#include <array>

std::vector<std::string> IpListSelection::LOCALHOST_NAMES = { "lo", "lo0" };

IpListSelection::IpListSelection(FDialog* parent) {
    struct ifaddrs* ifAddrStruct = NULL;
    struct ifaddrs* ifa = NULL;

    ipList = new FListView{parent};
    ipList->addColumn("IP Address");
    ipList->addColumn("Name");
    ipList->setGeometry(FPoint{2, 15}, FSize{42, 5});

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
}

int IpListSelection::select() {
    return 0;
}

void IpListSelection::hide() {
    ipList->hide();
}

void IpListSelection::show() {
    ipList->show();
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