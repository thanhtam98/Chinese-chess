#include "client.h"
#include "connectionBase.h"
#include <string>

void wClient::initEndpoint()
{

    // Set logging settings
    mEndpoint.set_error_channels(websocketpp::log::elevel::all);
    // m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
    // Initialize Asio
    mEndpoint.init_asio();
    mEndpoint.set_open_handshake_timeout(10000);
    // Set the default message handler to the echo handler
    mEndpoint.set_open_handler(
        std::bind(&wClient::onOpen, this, ::_1));
    mEndpoint.set_fail_handler(
        std::bind(&wClient::onFail, this, ::_1));
    mEndpoint.set_message_handler(std::bind(
        &wClient::onMessage, this, ::_1, ::_2));
    mEndpoint.set_close_handler(std::bind(
        &wClient::onClose, this, ::_1));

    mIsConnected = false;
}
wClient::wClient(string uri, int port)
{
    initEndpoint();

    mPort = port;
    mUri += uri;
    mUri += ":";
    mUri += std::to_string(mPort);
}

wClient::wClient()
{
    initEndpoint();
    mPort = DEFAULT_WPORT;
}

void wClient::_run() {
    mEndpoint.run();
}

void wClient::_setup() {
    mEndpoint.reset();
    websocketpp::lib::error_code ec;
    mUri = DEFAULT_WURI + mHost + ":" + std::to_string(mPort);
    LOG_F("URI: %s", mUri.c_str());
    client::connection_ptr cur_con = mEndpoint.get_connection(mUri, ec);

    if (ec) {
        LOG_F("Could not create connection because %s \n", ec.message());
        throw std::runtime_error("Could not create connection because " + ec.message());
    }

    mEndpoint.connect(cur_con);
}

int wClient::_send(std::string const payload) {
    if (payload.length() == 0)
        return -1;
    // if (mConnection == )
    if (mIsConnected == false)
        return -1;
    mEndpoint.send(mConnection, payload, DEFAULT_OPCODE);
    return 0;
}

void wClient::onFail(websocketpp::connection_hdl hdl) {
    LOG_F("Error happened");
    client::connection_ptr con = mEndpoint.get_con_from_hdl(hdl);
    if (con == nullptr) {
        LOG_F("Null pointer");
    }
    promise->set_exception(std::make_exception_ptr(std::runtime_error(con->get_ec().message())));
    promise.reset();
    con->terminate(websocketpp::lib::error_code());
}

void wClient::onOpen(websocketpp::connection_hdl hdl) {
    ConnectionBase::onOpen(hdl);
    promise->set_value();
    promise.reset();
}

void wClient::setHost(string host) {
    mHost = host;
}