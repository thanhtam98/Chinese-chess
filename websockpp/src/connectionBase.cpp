#include "connectionBase.h"
#include "server.h"
#include "client.h"

ConnectionBase* ConnectionBase::instance = nullptr;

ConnectionBase* ConnectionBase::getInstance() {
    if (instance == nullptr) {
        instance = new wServer();
    }
    return instance;
}

ConnectionBase* ConnectionBase::setInstance(connection_type type) {
    if (instance == nullptr) {
        switch (type) {
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
