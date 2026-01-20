#include "server.h"
#include "wConfig.h"
#include "log.h"

void wServer::initEndpoint()
{
    // Set logging settings
    mEndpoint.set_error_channels(websocketpp::log::elevel::all);
    // m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
    // Initialize Asio
    mEndpoint.init_asio();
    // Set the default message handler to the echo handler
    mEndpoint.set_open_handler(bind(&wServer::onOpen, this, ::_1));
    
    mEndpoint.set_message_handler(std::bind(
        &wServer::onMessage, this, ::_1, ::_2));
    mEndpoint.set_close_handler(std::bind(&wServer::onClose, this,
                                          ::_1));

    mIsConnected = false;
    initSem();
}
wServer::wServer()
{
    initEndpoint();
    mPort = DEFAULT_WPORT;
}

wServer::wServer(int port)
{
    initEndpoint();
    mPort = port;
}

void wServer::_setup() {
    // Listen on port 9000
    LOG_F("Listen on port 9000");
    mEndpoint.listen(mPort);
    // Queues a connection accept operation
    LOG_F("Queues a connection accept operation");
    mEndpoint.start_accept();
    // Start the Asio io_service run loop
    LOG_F("start the websocket server");
}

void wServer::_run(){
    mEndpoint.run();
    LOG_F("Run complete");
}

std::future<void> wServer::run(){
    std::promise<void> p;
    auto fut = p.get_future();
    try {
        _setup();    
    } catch (const std::exception &e) {
        LOG_F("Error : %s", e.what());
        p.set_exception(std::current_exception());
        return fut;
    }
    wThread = thread(std::bind(&wServer::_run, this));
    LOG_F("Run as a server");
    p.set_value();
    return fut;
}

int wServer::_send(std::string const payload)
{
    if (payload.length() == 0)
    {
        LOG_F(" Empty payload, not sending");
        return -1;
    }
    // if (mConnection == nullptr){
    //     LOG_F(" No connection established yet");
    //     return -1;
    // }
    if (mIsConnected == false){
        LOG_F(" Connection not established yet");
        return -1;
    }
    mEndpoint.send(mConnection, payload, DEFALUT_OPCODE);
    return 0;
}