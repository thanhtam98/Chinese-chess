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

void wServer::_run(){
    // Listen on port 9002
    mEndpoint.listen(mPort);
    // Queues a connection accept operation
    mEndpoint.start_accept();
    // Start the Asio io_service run loop
    LOG_F("start the websocket server");
    mEndpoint.run();
}
void wServer::run(){
    wThread = thread(std::bind(&wServer::_run, this));
}

int wServer::_send(std::string const payload)
{
    if (payload.length() == 0)
        return -1;
    // if (mConnection == )
    if (mIsConnected == false)
        return -1;
    mEndpoint.send(mConnection, payload, DEFALUT_OPCODE);
    return 0;
}