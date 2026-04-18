#include "connectionBase.h"
#include "server.h"
#include "client.h"
#include "configurator.h"

ConnectionBase* ConnectionBase::serverInstance = nullptr;
ConnectionBase* ConnectionBase::clientInstance = nullptr;
connection_type ConnectionBase::_type = WSERVER;
std::promise<void> ConnectionBase::waitOneClientPromise;

ConnectionBase* ConnectionBase::getInstance() {
    if (serverInstance == nullptr && clientInstance == nullptr){
        serverInstance = new wServer();
        return serverInstance;
    }
    if (_type == WSERVER) {
        return serverInstance;
    } else {
        return clientInstance;
    }
    return clientInstance;
}

ConnectionBase* ConnectionBase::setInstance(connection_type type) {
    _type = type;
    switch (type) {
        case WSERVER:
            LOG_F("Set Server");
            if (serverInstance == nullptr) {
                serverInstance = new wServer();
            }
            return serverInstance;
        case WCLIENT:
            LOG_F("Set Client");
            if (clientInstance == nullptr) {
                clientInstance = new wClient();
            }
            return clientInstance;
        default:
            return serverInstance;
    }
}

std::future<void> ConnectionBase::getEnoughConnection() {
    auto fut = waitOneClientPromise.get_future();

    LOG_F("Start to scan the connections");
    thread(&ConnectionBase::_scanConnections).detach();
    return fut;
}

int ConnectionBase::send(json js) {
    string payload = js.dump();
    LOG_F("Sending json: %s", payload.c_str());
    return _send(payload);
}

void ConnectionBase::setRecvCallback(ConnectionBaseCallback cb) {
    mCallback = cb;
}

void ConnectionBase::setConnectCallback(ConnectionBaseConnectCallback cb) {
    mConnectCallback = cb;
}

void ConnectionBase::onOpen() {
    mIsConnected = true;
    LOG_F("onOpen");
    if (mConnectCallback) {
        mConnectCallback();
    }
    // Start reading messages
    doRead();
}

void ConnectionBase::onMessage(const std::string& payload) {
    LOG_F("onMessage received: %s", payload.c_str());
    if (mCallback) {
        try {
            mCallback(json::parse(payload));
        } catch (const std::exception& e) {
            LOG_F("Error parsing JSON: %s", e.what());
        }
    }
}

void ConnectionBase::onClose() {
    mIsConnected = false;
    LOG_F("onClose");
}

void ConnectionBase::doRead() {
    if (!mWs || !mIsConnected) {
        return;
    }
    
    mWs->async_read(
        mBuffer,
        [this](beast::error_code ec, std::size_t bytes_transferred) {
            boost::ignore_unused(bytes_transferred);
            
            if (ec == websocket::error::closed) {
                onClose();
                return;
            }
            
            if (ec) {
                LOG_F("Read error: %s", ec.message().c_str());
                onClose();
                return;
            }
            
            // Process the message
            std::string payload = beast::buffers_to_string(mBuffer.data());
            mBuffer.consume(mBuffer.size());
            
            onMessage(payload);
            
            // Continue reading
            doRead();
        });
}

void ConnectionBase::_scanConnections() {
    while (ConnectionBase::getInstance()->connCount < 1) {
        this_thread::sleep_for(100ms);
    }
    LOG_F("Only accept one connection");
    waitOneClientPromise.set_value();
}

void ConnectionBase::setPort(uint16_t port) {
    mPort = port;
}