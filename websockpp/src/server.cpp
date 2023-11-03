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
        &wServer::msgHandler, this,
        std::placeholders::_1, std::placeholders::_2
    ));
}
wServer::wServer(){
    initEndpoint();
    mPort = DEFAULT_WPORT;
}

wServer::wServer(int port){
    initEndpoint();
    mPort = port;
}



void wServer::msgHandler(websocketpp::connection_hdl hdl, server::message_ptr msg){
    mEndpoint.send(hdl, msg->get_payload(), msg->get_opcode());
}

void  wServer::run(){
        // Listen on port 9002
        mEndpoint.listen(mPort);
        // Queues a connection accept operation
        mEndpoint.start_accept();
        // Start the Asio io_service run loop
        mEndpoint.run();
}