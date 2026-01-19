#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

#include "server.h"
#include "connectionBase.h"

int main(int argc, char* argv[]) {
    int port = DEFAULT_WPORT;
    if (argc > 1) {
        port = std::atoi(argv[1]);
    }

    wServer server(port);
    std::atomic<bool> got_message{false};

    server.setRecvCallback([&](json js) {
        std::cout << "server received: " << js.dump() << std::endl;
        json ack;
        ack["ack"] = true;
        server.send(ack);
        got_message = true;
    });

    std::thread server_thread(&wServer::_run, &server);
    server_thread.detach();

    // Wait for a message, then exit. Timeout keeps the process from hanging.
    auto start = std::chrono::steady_clock::now();
    while (!got_message.load()) {
        if (std::chrono::steady_clock::now() - start > std::chrono::seconds(10)) {
            std::cout << "server timeout waiting for message" << std::endl;
            return 1;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}
