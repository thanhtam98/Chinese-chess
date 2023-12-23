#pragma once

#include "utils.h"
#include "wConfig.h"
#include "connectionBase.h"

class wClient : public ConnectionBase{
public:
    wClient(string uri, int port);
    wClient();

    void run();
    void _run();

private:
    client mEndpoint;
    int mPort;
    string mUri;

    int _send(std::string const payload) override;
    
    
    void initEndpoint();
};
