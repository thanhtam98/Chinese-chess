#include "connectionBase.h"



int ConnectionBase::send(std::string const payload){

    /* Futher modification for payload  */
    return  _send(payload);    

}

void ConnectionBase::onOpen(websocketpp::connection_hdl hdl){
    mIsConnected = true;
    mConnection = hdl;
    cout << "onOpen" << endl;
        send(" this is open message message on both side ");



}
void ConnectionBase::onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg){
    
    cout << "onMessage" << endl;

}
void ConnectionBase::onClose(websocketpp::connection_hdl hdl){
    mIsConnected = false;
    // mConnection = nullptr;
    cout << "onClose" << endl;

}
