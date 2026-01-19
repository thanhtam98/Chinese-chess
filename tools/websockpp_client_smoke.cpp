#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

#include "client.h"
#include "connectionBase.h"

int main(int argc, char* argv[]) {
    std::string host = "ws://127.0.0.1";
    int port = DEFAULT_WPORT;
    if (argc > 1) {
        host = argv[1];
        if (host.rfind("ws://", 0) != 0 && host.rfind("wss://", 0) != 0) {
            host = "ws://" + host;
        }
    }
    if (argc > 2) {
        port = std::atoi(argv[2]);
    }

    wClient client(host, port);
    std::atomic<bool> got_ack{false};

    client.setRecvCallback([&](json js) {
        std::cout << "client received: " << js.dump() << std::endl;
        got_ack = true;
    });

    std::thread client_thread(&wClient::_run, &client);
    client_thread.detach();

    json msg;
    msg["opcode"] = 0;
    msg["from"] = {0, 0};
    msg["to"] = {1, 1};
    auto start = std::chrono::steady_clock::now();
    while (true) {
        if (client.send(msg) == 0) {
            break;
        }
        if (std::chrono::steady_clock::now() - start > std::chrono::seconds(5)) {
            std::cout << "client timeout waiting for connection" << std::endl;
            return 1;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    auto ack_start = std::chrono::steady_clock::now();
    while (!got_ack.load()) {
        if (std::chrono::steady_clock::now() - ack_start > std::chrono::seconds(5)) {
            std::cout << "client timeout waiting for ack" << std::endl;
            return 1;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}
