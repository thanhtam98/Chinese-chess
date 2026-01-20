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
    mUri += DEFAULT_WURI;
    mUri += ":";
    mUri += std::to_string(mPort);
}

void wClient::_setup() {
    websocketpp::lib::error_code ec;
    client::connection_ptr con = mEndpoint.get_connection(mUri, ec);

    if (ec) {
        LOG_F("Could not create connection because %s \n", ec.message());
        throw std::runtime_error("Could not create connection because " + ec.message());
    }

    mEndpoint.connect(con);
}

void wClient::_run() {
    mEndpoint.run();
}

std::future<void> wClient::run() {
    std::promise<void> p;
    auto fut = p.get_future();
    try {
        LOG_F("Setup client");
        _setup();    
    } catch (const std::exception &e) {
        LOG_F("Error : %s", e.what());
        p.set_exception(std::current_exception());
        return fut;
    }
    wThread = thread(std::bind(&wClient::_run, this));
    LOG_F("Run as a client");
    // Find some better approach than just waiting here,
    // Can think of both the success and fail callbacks of this connection
    std::this_thread::sleep_for(1s);
    if (!failMessage.empty()) {
        LOG_F("Error with the connection");
        p.set_exception(std::make_exception_ptr(std::runtime_error(failMessage)));
        return fut;
    }
    p.set_value();
    return fut;
}

int wClient::_send(std::string const payload) {
    if (payload.length() == 0)
        return -1;
    // if (mConnection == )
    if (mIsConnected == false)
        return -1;
    mEndpoint.send(mConnection, payload, DEFALUT_OPCODE);
    return 0;
}

void wClient::onFail(websocketpp::connection_hdl hdl) {
    LOG_F("Error happened");
    client::connection_ptr con = mEndpoint.get_con_from_hdl(hdl);
    if (con == nullptr) {
        LOG_F("Null pointer");
    }
    failMessage = con->get_ec().message();
}
