#pragma once

#include "utils.h"
#include "wConfig.h"
#include "connectionBase.h"

class wClient : public ConnectionBase{
public:
    wClient(string uri, int port);
    wClient();

    // std::future<void> run();

private:
    client mEndpoint;
    int mPort;
    string mUri;

    int _send(std::string const payload) override;
    void onOpen(websocketpp::connection_hdl hdl) override;
    void stopListening() override;
    
    void initEndpoint();
    void onFail(websocketpp::connection_hdl hdl);
    void _run() override;
    void _setup() override;
};
