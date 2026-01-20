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
    LOG_F("Sending json: %s", payload.c_str());
    /* Futher modification for payload  */
    return  _send(payload);    
}

void ConnectionBase::setRecvCallback(
            ConnectionBaseCallback cb){
    mCallback = cb;
}

void ConnectionBase::setConnectCallback(
            ConnectionBaseConnectCallback cb){
    mConnectCallback = cb;
}

void ConnectionBase::onOpen(websocketpp::connection_hdl hdl){
    mIsConnected = true;
    mConnection = hdl;
    LOG_F("onOpen");
    // Notify upper layers that connection is established
    if (mConnectCallback)
        mConnectCallback();
}
void ConnectionBase::onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg){

    LOG_F("onMessage received: %s", msg->get_payload().c_str());
    string payload = msg->get_payload();
    /* Call the upper layers*/
    if (mCallback)
        mCallback(json::parse(payload));

}
void ConnectionBase::onClose(websocketpp::connection_hdl hdl){
    mIsConnected = false;
    // mConnection = nullptr;
    LOG_F("onClose ");
}

void ConnectionBase::initSem(){

}
