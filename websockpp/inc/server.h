
#pragma once

#include "utils.h"
#include "wConfig.h"

typedef websocketpp::server<myConfig> server;

class wServer {
public:
    wServer();
    void msgHandler(websocketpp::connection_hdl hdl,
                         server::message_ptr msg);
    void run();
private:
    server mEndpoint;
};
