#include "client.h"
#include "connectionBase.h"
#include <string>

void wClient::initEndpoint(){

    // Set logging settings
    mEndpoint.set_error_channels(websocketpp::log::elevel::all);
    // m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
    // Initialize Asio
    mEndpoint.init_asio();
    // Set the default message handler to the echo handler
    mEndpoint.set_message_handler(std::bind(
        &wClient::onOpen, this,
        std::placeholders::_1, std::placeholders::_2
    ));
    mEndpoint.set_message_handler(std::bind(
        &wClient::onMessage, this,
        std::placeholders::_1, std::placeholders::_2
    ));
    mEndpoint.set_close_handler(std::bind(
        &wClient::onClose,this,
        std::placeholders::_1
    ));

    mIsConnected = false;
}
wClient::wClient(string uri, int port){
    initEndpoint();

    mPort = port;
    mUri += uri;
    mUri += ":";
    mUri += std::to_string(mPort);
}

wClient::wClient(){
    initEndpoint();

    mPort = DEFAULT_WPORT;
    mUri += DEFAULT_WURI;
    mUri += ":";
    mUri += std::to_string(mPort);
}


// void wClient::msgHandler(websocketpp::connection_hdl hdl, server::message_ptr msg)
// {
//    mEndpoint.send(hdl, msg->get_payload(), msg->get_opcode());
// }

void wClient::run(){
    websocketpp::lib::error_code ec;
    client::connection_ptr con = mEndpoint.get_connection(mUri,ec);

    if (ec){
        LOG_F(" Could not create connection because %s \n", ec.message());
        return;
    }

    mEndpoint.connect(con);
    mEndpoint.run();
}

int wClient::_send(std::string const payload){
    if (payload.length() == 0)
        return -1;
    // if (mConnection == )
    if (mIsConnected == false)
        return -1;   
    mEndpoint.send(mConnection, payload, DEFALUT_OPCODE);    
    return 0;
}

