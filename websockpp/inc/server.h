#pragma once

#include "wConfig.h"
#include "connectionBase.h"
#include <future>

class wServer : public ConnectionBase {
public:
    wServer(int port);
    wServer();
    ~wServer() override;
    
    std::future<void> run() override;

private:
    int mPort;
    std::shared_ptr<tcp::acceptor> mAcceptor;
    
    int _send(std::string const payload) override;
    void doAccept();
    void onAccept(beast::error_code ec, tcp::socket socket);
};
