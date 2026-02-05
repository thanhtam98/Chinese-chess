#include "server.h"
#include "log.h"

wServer::wServer() : mPort(DEFAULT_WPORT) {
    mIoc = std::make_shared<net::io_context>();
    mIsConnected = false;
}

wServer::wServer(int port) : mPort(port) {
    mIoc = std::make_shared<net::io_context>();
    mIsConnected = false;
}

wServer::~wServer() {
    if (mWs && mIsConnected) {
        beast::error_code ec;
        mWs->close(websocket::close_code::normal, ec);
    }
    if (mIoc) {
        mIoc->stop();
    }
    if (wThread.joinable()) {
        wThread.join();
    }
}

std::future<void> wServer::run() {
    std::promise<void> p;
    auto fut = p.get_future();
    
    try {
        LOG_F("Starting server on port %d", mPort);
        
        // Create acceptor
        mAcceptor = std::make_shared<tcp::acceptor>(
            *mIoc,
            tcp::endpoint(tcp::v4(), static_cast<unsigned short>(mPort))
        );
        
        // Start accepting connections
        doAccept();
        
        // Run io_context in a separate thread
        wThread = std::thread([this]() {
            LOG_F("Server io_context running");
            mIoc->run();
            LOG_F("Server io_context stopped");
        });
        
        LOG_F("Server started, waiting for connections");
        p.set_value();
        
    } catch (const std::exception& e) {
        LOG_F("Server error: %s", e.what());
        p.set_exception(std::current_exception());
    }
    
    return fut;
}

void wServer::doAccept() {
    mAcceptor->async_accept(
        [this](beast::error_code ec, tcp::socket socket) {
            onAccept(ec, std::move(socket));
        });
}

void wServer::onAccept(beast::error_code ec, tcp::socket socket) {
    if (ec) {
        LOG_F("Accept error: %s", ec.message().c_str());
        // Continue accepting
        doAccept();
        return;
    }
    
    LOG_F("Client connected");
    
    // Create WebSocket stream from the socket (using beast::tcp_stream for timeout support)
    mWs = std::make_shared<websocket::stream<beast::tcp_stream>>(std::move(socket));
    
    // Set suggested timeout settings for the websocket
    mWs->set_option(websocket::stream_base::timeout::suggested(
        beast::role_type::server));
    
    // Accept the WebSocket handshake
    mWs->async_accept(
        [this](beast::error_code ec) {
            if (ec) {
                LOG_F("WebSocket accept error: %s", ec.message().c_str());
                doAccept();
                return;
            }
            
            LOG_F("WebSocket handshake complete");
            onOpen();
            
            // For simplicity, only accept one connection at a time
            // If you need multiple connections, you'd need to manage them separately
        });
}

int wServer::_send(std::string const payload) {
    if (payload.empty()) {
        LOG_F("Empty payload, not sending");
        return -1;
    }
    
    if (!mIsConnected || !mWs) {
        LOG_F("Connection not established yet");
        return -1;
    }
    
    try {
        std::lock_guard<std::mutex> lock(mSendMutex);
        mWs->text(true);
        mWs->write(net::buffer(payload));
        return 0;
    } catch (const std::exception& e) {
        LOG_F("Send error: %s", e.what());
        return -1;
    }
}
