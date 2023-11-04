#include "server.h"
#include "wConfig.h"


void wServer::initEndpoint(){
    // Set logging settings
    mEndpoint.set_error_channels(websocketpp::log::elevel::all);
    // m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
    // Initialize Asio
    mEndpoint.init_asio();
    // Set the default message handler to the echo handler
    mEndpoint.set_message_handler(std::bind(
        &wServer::onOpen, this,
        std::placeholders::_1, std::placeholders::_2
    ));
    mEndpoint.set_message_handler(std::bind(
        &wServer::onMessage, this,
        std::placeholders::_1, std::placeholders::_2
    ));
    mEndpoint.set_close_handler(std::bind(
        &wServer::onClose,this,
        std::placeholders::_1
    ));

    mIsConnected = false;
}
wServer::wServer(){
    initEndpoint();
    mPort = DEFAULT_WPORT;
}

wServer::wServer(int port){
    initEndpoint();
    mPort = port;

}


void  wServer::run(){
    // Listen on port 9002
    mEndpoint.listen(mPort);
    // Queues a connection accept operation
    mEndpoint.start_accept();
    // Start the Asio io_service run loop
    mEndpoint.run();
}

int wServer::_send(std::string const payload){
    if (payload.length() == 0)
        return -1;
    // if (mConnection == )
    if (mIsConnected == false)
        return -1;   
    mEndpoint.send(mConnection, payload, DEFALUT_OPCODE);    
    return 0;
}