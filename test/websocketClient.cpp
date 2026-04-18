// Simple WebSocket Client using Boost.Beast for testing
// Usage: Run this and use commands like:
//   connect ws://localhost:9000
//   send 0 {"test": "message"}
//   show 0
//   close 0
//   quit

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <thread>
#include <memory>
#include <mutex>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class connection_metadata {
public:
    typedef std::shared_ptr<connection_metadata> ptr;

    connection_metadata(int id, const std::string& uri, net::io_context& ioc)
        : m_id(id)
        , m_uri(uri)
        , m_status("Connecting")
        , m_ioc(ioc)
        , m_resolver(net::make_strand(ioc))
        , m_ws(net::make_strand(ioc))
    {}

    void connect(const std::string& host, const std::string& port) {
        m_host = host;
        m_port = port;
        
        // Look up the domain name
        m_resolver.async_resolve(
            host,
            port,
            beast::bind_front_handler(
                &connection_metadata::on_resolve,
                shared_from_this()));
    }

    void on_resolve(beast::error_code ec, tcp::resolver::results_type results) {
        if (ec) {
            m_status = "Failed";
            m_error_reason = "Resolve failed: " + ec.message();
            return;
        }

        beast::get_lowest_layer(m_ws).expires_after(std::chrono::seconds(30));

        beast::get_lowest_layer(m_ws).async_connect(
            results,
            beast::bind_front_handler(
                &connection_metadata::on_connect,
                shared_from_this()));
    }

    void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep) {
        if (ec) {
            m_status = "Failed";
            m_error_reason = "Connect failed: " + ec.message();
            return;
        }

        beast::get_lowest_layer(m_ws).expires_never();

        m_ws.set_option(websocket::stream_base::timeout::suggested(
            beast::role_type::client));

        std::string host = m_host + ":" + m_port;
        m_ws.async_handshake(host, "/",
            beast::bind_front_handler(
                &connection_metadata::on_handshake,
                shared_from_this()));
    }

    void on_handshake(beast::error_code ec) {
        if (ec) {
            m_status = "Failed";
            m_error_reason = "Handshake failed: " + ec.message();
            return;
        }

        m_status = "Open";
        do_read();
    }

    void do_read() {
        m_ws.async_read(
            m_buffer,
            beast::bind_front_handler(
                &connection_metadata::on_read,
                shared_from_this()));
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (ec == websocket::error::closed) {
            m_status = "Closed";
            return;
        }

        if (ec) {
            m_status = "Error";
            m_error_reason = "Read error: " + ec.message();
            return;
        }

        std::cout << "Received message: " << beast::buffers_to_string(m_buffer.data()) << std::endl;
        m_buffer.consume(m_buffer.size());

        do_read();
    }

    void send(const std::string& message) {
        if (m_status != "Open") {
            std::cout << "> Connection not open" << std::endl;
            return;
        }

        m_ws.text(true);
        m_ws.write(net::buffer(message));
    }

    void close() {
        if (m_status != "Open") {
            std::cout << "> Connection not open" << std::endl;
            return;
        }

        m_ws.async_close(websocket::close_code::normal,
            beast::bind_front_handler(
                &connection_metadata::on_close,
                shared_from_this()));
    }

    void on_close(beast::error_code ec) {
        if (ec) {
            m_error_reason = "Close error: " + ec.message();
        }
        m_status = "Closed";
    }

    std::shared_ptr<connection_metadata> shared_from_this() {
        return std::shared_ptr<connection_metadata>(this, [](connection_metadata*){});
    }

    friend std::ostream& operator<<(std::ostream& out, const connection_metadata& data);

private:
    int m_id;
    std::string m_uri;
    std::string m_host;
    std::string m_port;
    std::string m_status;
    std::string m_error_reason;
    
    net::io_context& m_ioc;
    tcp::resolver m_resolver;
    websocket::stream<beast::tcp_stream> m_ws;
    beast::flat_buffer m_buffer;
};

std::ostream& operator<<(std::ostream& out, const connection_metadata& data) {
    out << "> URI: " << data.m_uri << "\n"
        << "> Status: " << data.m_status << "\n"
        << "> Error/close reason: " << (data.m_error_reason.empty() ? "N/A" : data.m_error_reason);
    return out;
}

class websocket_endpoint {
public:
    websocket_endpoint() : m_next_id(0), m_work_guard(net::make_work_guard(m_ioc)) {
        m_thread = std::thread([this]() {
            m_ioc.run();
        });
    }

    ~websocket_endpoint() {
        m_work_guard.reset();
        m_ioc.stop();
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }

    int connect(const std::string& uri) {
        // Parse URI: ws://host:port or host:port
        std::string clean_uri = uri;
        if (clean_uri.find("ws://") == 0) {
            clean_uri = clean_uri.substr(5);
        } else if (clean_uri.find("wss://") == 0) {
            clean_uri = clean_uri.substr(6);
        }

        std::string host, port = "80";
        size_t colon_pos = clean_uri.find(':');
        if (colon_pos != std::string::npos) {
            host = clean_uri.substr(0, colon_pos);
            port = clean_uri.substr(colon_pos + 1);
        } else {
            host = clean_uri;
        }

        int new_id = m_next_id++;
        auto metadata = std::make_shared<connection_metadata>(new_id, uri, m_ioc);
        m_connection_list[new_id] = metadata;
        
        metadata->connect(host, port);
        
        return new_id;
    }

    connection_metadata::ptr get_metadata(int id) const {
        auto it = m_connection_list.find(id);
        if (it == m_connection_list.end()) {
            return nullptr;
        }
        return it->second;
    }

    void send(int id, const std::string& message) {
        auto metadata = get_metadata(id);
        if (!metadata) {
            std::cout << "> No connection found with id " << id << std::endl;
            return;
        }
        metadata->send(message);
    }

    void close(int id) {
        auto metadata = get_metadata(id);
        if (!metadata) {
            std::cout << "> No connection found with id " << id << std::endl;
            return;
        }
        metadata->close();
    }

private:
    net::io_context m_ioc;
    net::executor_work_guard<net::io_context::executor_type> m_work_guard;
    std::thread m_thread;
    std::map<int, connection_metadata::ptr> m_connection_list;
    int m_next_id;
};

int main() {
    bool done = false;
    std::string input;
    websocket_endpoint endpoint;

    std::cout << "Boost.Beast WebSocket Client" << std::endl;
    std::cout << "Type 'help' for commands" << std::endl;

    while (!done) {
        std::cout << "Enter Command: ";
        std::getline(std::cin, input);

        if (input == "quit") {
            done = true;
        } else if (input == "help") {
            std::cout
                << "\nCommand List:\n"
                << "connect <ws uri>      - Connect to a WebSocket server\n"
                << "show <connection id>  - Show connection status\n"
                << "send <id> <message>   - Send a message\n"
                << "close <id>            - Close connection\n"
                << "help                  - Display this help text\n"
                << "quit                  - Exit the program\n"
                << std::endl;
        } else if (input.substr(0, 7) == "connect") {
            if (input.length() > 8) {
                int id = endpoint.connect(input.substr(8));
                std::cout << "> Created connection with id " << id << std::endl;
            } else {
                std::cout << "> Usage: connect <ws uri>" << std::endl;
            }
        } else if (input.substr(0, 4) == "show") {
            int id = atoi(input.substr(5).c_str());
            auto metadata = endpoint.get_metadata(id);
            if (metadata) {
                std::cout << *metadata << std::endl;
            } else {
                std::cout << "> Unknown connection id " << id << std::endl;
            }
        } else if (input.substr(0, 4) == "send") {
            std::stringstream ss(input);
            std::string cmd;
            int id;
            std::string message;
            
            ss >> cmd >> id;
            std::getline(ss, message);
            if (!message.empty() && message[0] == ' ') {
                message = message.substr(1);
            }
            
            endpoint.send(id, message);
        } else if (input.substr(0, 5) == "close") {
            std::stringstream ss(input);
            std::string cmd;
            int id;
            
            ss >> cmd >> id;
            endpoint.close(id);
        } else if (!input.empty()) {
            std::cout << "> Unrecognized Command" << std::endl;
        }
    }

    return 0;
}
