
#pragma once

#include "utils.h"
#include "wConfig.h"

class wServer {
public:
    wServer(int port);
    wServer();
    void msgHandler(websocketpp::connection_hdl hdl,
                         server::message_ptr msg);
    void run();
private:
    server mEndpoint;
    int mPort;

    void initEndpoint();
};
