#include "client.h"
#include "log.h"

wClient::wClient() 
    : mPort(DEFAULT_WPORT), mHost(DEFAULT_WURI) {
    mIoc = std::make_shared<net::io_context>();
    mIsConnected = false;
}

wClient::wClient(string uri, int port) 
    : mPort(port), mHost(uri) {
    mIoc = std::make_shared<net::io_context>();
    mIsConnected = false;
    
    // Remove ws:// or wss:// prefix if present
    if (mHost.find("ws://") == 0) {
        mHost = mHost.substr(5);
    } else if (mHost.find("wss://") == 0) {
        mHost = mHost.substr(6);
    }
}

wClient::~wClient() {
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

std::future<void> wClient::run() {
    promise = std::make_unique<std::promise<void>>();
    auto fut = promise->get_future();
    
    try {
        LOG_F("Connecting to %s:%d", mHost.c_str(), mPort);
        
        mResolver = std::make_shared<tcp::resolver>(*mIoc);
        mWs = std::make_shared<websocket::stream<beast::tcp_stream>>(net::make_strand(*mIoc));
        
        // Start the asynchronous connection process
        doConnect();
        
        // Run io_context in a separate thread
        wThread = std::thread([this]() {
            LOG_F("Client io_context running");
            mIoc->run();
            LOG_F("Client io_context stopped");
        });
        
        // Wait a bit for connection to establish
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        if (!mFailMessage.empty()) {
            LOG_F("Connection failed: %s", mFailMessage.c_str());
            promise->set_exception(std::make_exception_ptr(
                std::runtime_error(mFailMessage)));
        } else {
            promise->set_value();
        }
        
    } catch (const std::exception& e) {
        LOG_F("Client error: %s", e.what());
        promise->set_exception(std::current_exception());
    }
    
    return fut;
}

void wClient::doConnect() {
    // Look up the domain name
    mResolver->async_resolve(
        mHost,
        std::to_string(mPort),
        [this](beast::error_code ec, tcp::resolver::results_type results) {
            onResolve(ec, results);
        });
}

void wClient::onResolve(beast::error_code ec, tcp::resolver::results_type results) {
    if (ec) {
        mFailMessage = "Resolve failed: " + ec.message();
        LOG_F("%s", mFailMessage.c_str());
        return;
    }
    
    // Set the timeout for the connect operation
    beast::get_lowest_layer(*mWs).expires_after(std::chrono::seconds(30));
    
    // Make the connection
    beast::get_lowest_layer(*mWs).async_connect(
        results,
        [this](beast::error_code ec, tcp::resolver::results_type::endpoint_type ep) {
            onConnect(ec, ep);
        });
}

void wClient::onConnect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep) {
    if (ec) {
        mFailMessage = "Connect failed: " + ec.message();
        LOG_F("%s", mFailMessage.c_str());
        return;
    }
    
    LOG_F("TCP connected to %s:%d", ep.address().to_string().c_str(), ep.port());
    
    // Turn off the timeout on the tcp_stream, because the websocket stream has its own timeout system
    beast::get_lowest_layer(*mWs).expires_never();
    
    // Set suggested timeout settings for the websocket
    mWs->set_option(websocket::stream_base::timeout::suggested(
        beast::role_type::client));
    
    // Set a decorator to change the User-Agent
    mWs->set_option(websocket::stream_base::decorator(
        [](websocket::request_type& req) {
            req.set(beast::http::field::user_agent,
                std::string(BOOST_BEAST_VERSION_STRING) + " chinese-chess-client");
        }));
    
    // Perform the WebSocket handshake
    std::string host = mHost + ":" + std::to_string(mPort);
    mWs->async_handshake(host, "/",
        [this](beast::error_code ec) {
            onHandshake(ec);
        });
}

void wClient::onHandshake(beast::error_code ec) {
    if (ec) {
        mFailMessage = "Handshake failed: " + ec.message();
        LOG_F("%s", mFailMessage.c_str());
        return;
    }
    
    LOG_F("WebSocket handshake complete");
    onOpen();
}

int wClient::_send(std::string const payload) {
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

void wClient::setHost(string host) {
    mHost = host;
}