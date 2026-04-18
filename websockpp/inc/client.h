#pragma once

#include "wConfig.h"
#include "connectionBase.h"
#include <future>

class wClient : public ConnectionBase {
public:
    wClient(string uri, int port);
    wClient();
    ~wClient() override;

    std::future<void> run() override;
    void setHost(string host) override;
private:
    int mPort;
    string mHost;
    std::shared_ptr<tcp::resolver> mResolver;
    
    int _send(std::string const payload) override;
    void doConnect();
    void onResolve(beast::error_code ec, tcp::resolver::results_type results);
    void onConnect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep);
    void onHandshake(beast::error_code ec);
    
    std::string mFailMessage;
};
