#pragma once

#include "server.h"
#include "client.h"
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
                std::cout << "[MY_LOGGER]" << ...
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
    typedef websocketpp::transport::asio::endpoint<my_transport_config>
        transport_type;
};

// typedef my_server::connection_type my_connection;
