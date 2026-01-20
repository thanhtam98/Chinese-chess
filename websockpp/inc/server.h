#pragma once
#include "utils.h"
#include "wConfig.h"
#include "connectionBase.h"
#include <future>

class wServer : public ConnectionBase {
public:
    wServer(int port);
    wServer();
    std::future<void> run() override;
    void _run();
    void _setup();
private:
    server mEndpoint;
    int mPort;

    int _send(std::string const payload) override;

    // void msgHandler(websocketpp::connection_hdl hdl,
    //                      server::message_ptr msg);
    // void onOpen(websocketpp::connection_hdl hdl,
    //             server::message_ptr msg);

    void initEndpoint();
};
