#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/connection.hpp>

#include <websocketpp/logger/syslog.hpp>
#include <websocketpp/extensions/permessage_deflate/enabled.hpp>
#include <functional>
#include "log.h"
#define DEFAULT_WPORT 9000
#define DEFAULT_WURI "ws://localhost"
#define DEFALUT_OPCODE   websocketpp::frame::opcode::TEXT

namespace websocketpp
{
    namespace log
    {
        template <typename concurrency, typename names>
        class myLogger : public basic<concurrency, names>
        {
        public:
            typedef basic<concurrency, names> base;

            myLogger<concurrency, names>(channel_type_hint::value hint = channel_type_hint::access)
                : basic<concurrency, names>(hint), m_channel_type_hint(hint)
            {
            }

            myLogger<concurrency, names>(level channels, channel_type_hint::value hint = channel_type_hint::access)
                : basic<concurrency, names>(channels, hint), m_channel_type_hint(hint)
            {
            }

            void write(level channel, std::string const &msg)
            {
                write(channel, msg.c_str());
            }

            void write(level channel, char const *msg)
            {
                scoped_lock_type lock(base::m_lock);
                if (!this->dynamic_test(channel))
                    return;
                // custom logging, e.g.: std::cout with specific format:
                // std::cout << "[WEBSOCKPP]" << msg;
                // LOG_F("[WEBSOCKPP] %s", msg.);
            }

        private:
            typedef typename base::scoped_lock_type scoped_lock_type;
            channel_type_hint::value m_channel_type_hint;
        };
    } // log
} // websocketpp

struct myConfig : public websocketpp::config::asio
{
    typedef websocketpp::log::myLogger<concurrency_type, websocketpp::log::elevel> elog_type;
    typedef websocketpp::log::myLogger<concurrency_type, websocketpp::log::alevel> alog_type;
    // create a custom transport config based on the base asio transport config
    struct my_transport_config : public websocketpp::config::asio::transport_config
    {
        // just override the logger types
        typedef myConfig::alog_type alog_type;
        typedef myConfig::elog_type elog_type;
    };

    // let `myConfig` know to create transport endpoints with `my_transport_config`
    typedef websocketpp::transport::asio::endpoint<my_transport_config> transport_type;
};


// typedef websocketpp::client<websocketpp::config::asio> client;
// typedef websocketpp::server<websocketpp::config::asio> server;

typedef websocketpp::server<myConfig> server;
typedef websocketpp::client<myConfig> client;
typedef websocketpp::endpoint<websocketpp::connection<myConfig>,myConfig> endpoint;
typedef websocketpp::connection_hdl connection;
// typedef websocketpp::config::asio_client::message_type::ptr message_ptr;


using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;