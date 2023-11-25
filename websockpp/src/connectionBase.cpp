#include "connectionBase.h"
#include "server.h"
#include "client.h"

ConnectionBase* ConnectionBase::instance = nullptr;

ConnectionBase* ConnectionBase::getInstance(){
    if (instance == nullptr){
        instance = new wServer();
    }
    return instance;
}

ConnectionBase* ConnectionBase::setInstance(connection_type type){
    if (instance == nullptr){
        switch (type)
        {
        case WSERVER:
            instance = new wServer();
            break;
        case WCLIENT:
            instance = new wClient();
            break;
        default:
            break;
        }
    }
    return instance;
}


int ConnectionBase::send(json js){
    
    string payload = js.dump();
    // cout <<" Sending" <<payload << endl;
    /* Futher modification for payload  */
    return  _send(payload);    
}

void ConnectionBase::setRecvCallback(
            ConnectionBaseCallback cb){
    mCallback = cb;
}


void ConnectionBase::onOpen(websocketpp::connection_hdl hdl){
    mIsConnected = true;
    mConnection = hdl;
    // cout << "onOpen" << endl;

}
void ConnectionBase::onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg){

    // cout << "onMessage" << msg->get_payload() << endl;
    string payload = msg->get_payload();
    /* Call the upper layers*/
    if (mCallback)
        mCallback(json::parse(payload));

}
void ConnectionBase::onClose(websocketpp::connection_hdl hdl){
    mIsConnected = false;
    // mConnection = nullptr;
    // cout << "onClose" << endl;

}

void ConnectionBase::initSem(){

}