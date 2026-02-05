#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/connect.hpp>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include "log.h"

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

#define DEFAULT_WPORT 9000
#define DEFAULT_WURI "localhost"

// Placeholders for bind
using std::placeholders::_1;
using std::placeholders::_2;
