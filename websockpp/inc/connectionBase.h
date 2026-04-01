#pragma once

#include "wConfig.h"
#include "utils.h"
#undef null
#include <nlohmann/json.hpp>
#include <semaphore.h>
#include <queue>
#include <future>

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
} ;

typedef std::function<void (json js)> ConnectionBaseCallback;
typedef std::function<void (void)> ConnectionBaseConnectCallback;

class ConnectionBase {
public:
    static ConnectionBase* setInstance(connection_type type);
    static ConnectionBase* getInstance();
    static connection_type _type;
    std::future<void> run();
    static std::future<void> getEnoughConnection();
    int send(json const js);
    void setRecvCallback(ConnectionBaseCallback cb);
    void setConnectCallback(ConnectionBaseConnectCallback cb);

    virtual int _send(std::string const payload) = 0;
    string _recv(void);
    int connCount = 0;
private:
protected:
    static ConnectionBase* instance;
    static std::promise<void> waitOneClientPromise;
    std::thread wThread;
    connection mConnection;
    ConnectionBaseCallback mCallback;
    ConnectionBaseConnectCallback mConnectCallback;
    bool mIsConnected;
    std::unique_ptr<std::promise<void>> promise;
    /* temporary for connection established status
    *  because we don't know what mConnection's constructor is
    */
    virtual void _run() = 0;
    virtual void _setup() = 0;
    static void _scanConnections();
    virtual void stopListening() = 0;
    virtual void onOpen(websocketpp::connection_hdl hdl);
    void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg);
    void onClose(websocketpp::connection_hdl hdl);
    void initSem();
};
