#include "connectionBase.h"
#include "server.h"
#include "client.h"

ConnectionBase* ConnectionBase::instance = nullptr;
connection_type ConnectionBase::_type = WSERVER;
std::promise<void> ConnectionBase::waitOneClientPromise;

ConnectionBase* ConnectionBase::getInstance(){
    if (instance == nullptr){
        instance = new wServer();
    }
    return instance;
}

ConnectionBase* ConnectionBase::setInstance(connection_type type){
    _type = type;
    switch (type) {
        case WSERVER:
            LOG_F("Set Server");
            instance = new wServer();
            break;
        case WCLIENT:
            LOG_F("Set Client");
            instance = new wClient();
            break;
        default:
            break;
    }
    return instance;
}

std::future<void> ConnectionBase::getEnoughConnection() {
    auto fut = waitOneClientPromise.get_future();

    LOG_F("Start to scan the connections");
    thread(&ConnectionBase::_scanConnections).detach();
    return fut;
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

std::future<void> ConnectionBase::run() {
    promise = std::make_unique<std::promise<void>>();
    auto fut = promise->get_future();
    try {
        LOG_F("Setup server or client");
        _setup();    
    } catch (const std::exception &e) {
        LOG_F("Error : %s", e.what());
        promise->set_exception(std::current_exception());
        promise.reset();
        return fut;
    }

    if (wThread.joinable()) {
        wThread.join(); 
    }

    wThread = thread(&ConnectionBase::_run, this);
    LOG_F("Run as a server or client");
    return fut;
}

void ConnectionBase::_scanConnections() {
    while (ConnectionBase::getInstance()->connCount < 1) {
        this_thread::sleep_for(100ms);
    }
    LOG_F("Only accept one connection");
    waitOneClientPromise.set_value();
}