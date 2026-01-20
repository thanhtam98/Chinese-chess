#pragma once

#include "utils.h"
#include "wConfig.h"
#include "connectionBase.h"

class wClient : public ConnectionBase{
public:
    wClient(string uri, int port);
    wClient();

    std::future<void> run();
    void _run();
    void _setup();

private:
    client mEndpoint;
    int mPort;
    string mUri;

    int _send(std::string const payload) override;
    
    
    void initEndpoint();
    void onFail(websocketpp::connection_hdl hdl);
    std::string failMessage;
};
