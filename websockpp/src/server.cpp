#include "server.h"
#include "wConfig.h"
#include "log.h"

void wServer::initEndpoint()
{
    // Set logging settings
    mEndpoint.set_error_channels(websocketpp::log::elevel::all);
    // m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
    // Initialize Asio
    mEndpoint.init_asio();
    // Set the default message handler to the echo handler
    mEndpoint.set_open_handler(bind(&wServer::onOpen, this, ::_1));
    mEndpoint.set_fail_handler(
        std::bind(&wServer::onFail, this, ::_1));
    mEndpoint.set_message_handler(std::bind(
        &wServer::onMessage, this, ::_1, ::_2));
    mEndpoint.set_close_handler(std::bind(&wServer::onClose, this, ::_1));

    mIsConnected = false;
    initSem();
}
wServer::wServer()
{
    initEndpoint();
    mPort = DEFAULT_WPORT;
}

wServer::wServer(int port)
{
    initEndpoint();
    mPort = port;
}

void wServer::_setup() {
    std::error_code ec;
    mEndpoint.listen(mPort, ec);
    LOG_F("Listen on port %d, error: %s", mPort, ec.message().c_str());
    // Queues a connection accept operation
    LOG_F("Queues a connection accept operation");
    mEndpoint.start_accept();
    // Start the Asio io_service run loop
    LOG_F("start the websocket server");
    promise->set_value();
    promise.reset();
}

int wServer::_send(std::string const payload)
{
    if (payload.length() == 0) {
        LOG_F(" Empty payload, not sending");
        return -1;
    }
    if (mIsConnected == false) {
        LOG_F(" Connection not established yet");
        return -1;
    }
    mEndpoint.send(mConnection, payload, DEFAULT_OPCODE);
    return 0;
}

void wServer::onFail(websocketpp::connection_hdl hdl) {
    LOG_F("Error happened");
    client::connection_ptr con = mEndpoint.get_con_from_hdl(hdl);
    if (con == nullptr) {
        LOG_F("Null pointer");
    }
    LOG_F("Failed because: %s", con->get_ec().message().c_str());
    // Ignore Operation Canceled Error, which is the result of stop_listening
    if (con->get_ec() != websocketpp::error::operation_canceled) {
        LOG_F("Report the error");
        promise->set_exception(std::make_exception_ptr(std::runtime_error(con->get_ec().message())));
        promise.reset();
    }
}

void wServer::_run() {
    mEndpoint.run();
}

void wServer::onOpen(websocketpp::connection_hdl hdl) {
    ConnectionBase::onOpen(hdl);
    connCount++;
    LOG_F("Stop listening because we only need one client");
    mEndpoint.stop_listening();
}

void wServer::setHost(string host) {
    // Ignore completely
}