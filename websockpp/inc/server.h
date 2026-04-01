#pragma once
#include "utils.h"
#include "wConfig.h"
#include "connectionBase.h"
#include <future>

class wServer : public ConnectionBase {
public:
    wServer(int port);
    wServer();
    // std::future<void> run() override;
private:
    server mEndpoint;

    int _send(std::string const payload) override;

    // void msgHandler(websocketpp::connection_hdl hdl,
    //                      server::message_ptr msg);
    // void onOpen(websocketpp::connection_hdl hdl,
    //             server::message_ptr msg);

    void initEndpoint();
    void onFail(websocketpp::connection_hdl hdl);
    void onOpen(websocketpp::connection_hdl hdl) override;
    void _run() override;
    void _setup() override;
};