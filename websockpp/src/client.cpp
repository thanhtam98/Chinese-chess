#include "client.h"
#include <string>

void wClient::initEndpoint(){

    mEndpoint.set_error_channels(websocketpp::log::elevel::all);

    mEndpoint.init_asio();

    mEndpoint.set_message_handler(std::bind(
        &wClient::msgHandler, this,
        std::placeholders::_1, std::placeholders::_2
    ));
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


void wClient::msgHandler(websocketpp::connection_hdl hdl, server::message_ptr msg)
{
   mEndpoint.send(hdl, msg->get_payload(), msg->get_opcode());
}

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

