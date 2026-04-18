#pragma once

#include "wConfig.h"
#include "utils.h"
#undef null
#include <nlohmann/json.hpp>
#include <queue>
#include <future>
#include <mutex>

using json = nlohmann::json;
/**
 *  This interface indicates functions that have several features supporing communication. 
 *  MOVE From To 
 *  SEL  From
*/

enum connection_type {
    WSERVER,
    WCLIENT,
    NON_CONNECTION
};

typedef std::function<void(json js)> ConnectionBaseCallback;
typedef std::function<void(void)> ConnectionBaseConnectCallback;

class ConnectionBase {
public:
    static ConnectionBase* setInstance(connection_type type);
    static ConnectionBase* getInstance();
    static connection_type _type;
    int connCount = 0;
    virtual std::future<void> run() = 0;
    static std::future<void> getEnoughConnection();
    int send(json const js);
    void setRecvCallback(ConnectionBaseCallback cb);
    void setConnectCallback(ConnectionBaseConnectCallback cb);

    virtual int _send(std::string const payload) = 0;
    void setPort(uint16_t port);
    virtual void setHost(string host) = 0;
    string _recv(void);
    
    virtual ~ConnectionBase() = default;

protected:
    static ConnectionBase* serverInstance;
    static ConnectionBase* clientInstance;
    static std::promise<void> waitOneClientPromise;
    std::thread wThread;
    uint16_t mPort;
    
    // Boost.Beast types
    std::shared_ptr<net::io_context> mIoc;
    std::shared_ptr<websocket::stream<beast::tcp_stream>> mWs;
    beast::flat_buffer mBuffer;
    
    ConnectionBaseCallback mCallback;
    ConnectionBaseConnectCallback mConnectCallback;
    bool mIsConnected;
    std::mutex mSendMutex;
    std::unique_ptr<std::promise<void>> promise;
    
    static void _scanConnections();

    void onOpen();
    void onMessage(const std::string& payload);
    void onClose();
    void doRead();
};
