

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <functional>

#pragma once

#include "utils.h"
#include "websockpp.h"

#include <websocketpp/logger/syslog.hpp>
#include <websocketpp/extensions/permessage_deflate/enabled.hpp>



namespace websocketpp
{
    namespace log
    {
        template<typename concurrency, typename names>
        class my_logger : public basic<concurrency, names>
        {
        public:
            typedef basic<concurrency, names> base;

            my_logger<concurrency, names>(channel_type_hint::value hint = channel_type_hint::access)
                    : basic<concurrency, names>(hint), m_channel_type_hint(hint)
            {
            }

            my_logger<concurrency, names>(level channels, channel_type_hint::value hint = channel_type_hint::access)
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
                if(!this->dynamic_test(channel)) return;
                // custom logging, e.g.: std::cout with specific format:
                std::cout << "[MY_LOGGER]" << msg;
                // add to Flog
            }

        private:
            typedef typename base::scoped_lock_type scoped_lock_type;
            channel_type_hint::value m_channel_type_hint;
        };
    } // log
} // websocketpp

struct my_config : public websocketpp::config::asio
{
    typedef websocketpp::log::my_logger<concurrency_type, websocketpp::log::elevel> elog_type;
    typedef websocketpp::log::my_logger<concurrency_type, websocketpp::log::alevel> alog_type;
       // create a custom transport config based on the base asio transport config
    struct my_transport_config : public websocketpp::config::asio::transport_config {
        // just override the logger types
        typedef my_config::alog_type alog_type;
        typedef my_config::elog_type elog_type;
    };
    
    // let `my_config` know to create transport endpoints with `my_transport_config`
    typedef websocketpp::transport::asio::endpoint<my_transport_config> transport_type;
};
typedef websocketpp::server<my_config> server;

class utility_server {
public:
    utility_server() {
         // Set logging settings
        m_endpoint.set_error_channels(websocketpp::log::elevel::all);
        // m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        m_endpoint.init_asio();

        // Set the default message handler to the echo handler
        m_endpoint.set_message_handler(std::bind(
            &utility_server::echo_handler, this,
            std::placeholders::_1, std::placeholders::_2
        ));
    }

    void echo_handler(websocketpp::connection_hdl hdl, server::message_ptr msg) {
        // write a new message
        m_endpoint.send(hdl, msg->get_payload(), msg->get_opcode());
    }

    void run() {
        // Listen on port 9002
        m_endpoint.listen(9002);

        // Queues a connection accept operation
        m_endpoint.start_accept();

        // Start the Asio io_service run loop
        m_endpoint.run();
    }
private:
    server m_endpoint;
};

// int main() {
//     utility_server s;
//     s.run();
//     return 0;
// }