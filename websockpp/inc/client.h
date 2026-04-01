#pragma once

#include "utils.h"
#include "wConfig.h"
#include "connectionBase.h"

class wClient : public ConnectionBase{
public:
    wClient(string uri, int port);
    wClient();

    // std::future<void> run();
    void setHost(string host) override;
private:
    client mEndpoint;
    string mUri;
    string mHost;

    int _send(std::string const payload) override;
    void onOpen(websocketpp::connection_hdl hdl) override;
    
    void initEndpoint();
    void onFail(websocketpp::connection_hdl hdl);
    void _run() override;
    void _setup() override;
};
