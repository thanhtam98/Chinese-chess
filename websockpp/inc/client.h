#pragma once

#include "utils.h"
#include "wConfig.h"

class wClient{
    public:
        wClient(string uri, int port);
        wClient();
        void msgHandler(websocketpp::connection_hdl hdl, server::message_ptr msg);
        void run();

    private:
        client mEndpoint;
        int mPort;
        string mUri;
        
        void initEndpoint();
};
