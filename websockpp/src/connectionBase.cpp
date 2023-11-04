#include "connectionBase.h"



int ConnectionBase::send(std::string const payload){

    /* Futher modification for payload  */
    return  _send(payload);    

}

void ConnectionBase::onOpen(websocketpp::connection_hdl hdl, server::message_ptr msg){
    mIsConnected = true;
    mConnection = hdl;   
}
void ConnectionBase::onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg){
    mIsConnected = false;
    

}
void ConnectionBase::onClose(websocketpp::connection_hdl hdl){
    mIsConnected = false;
    // mConnection = nullptr;
}
