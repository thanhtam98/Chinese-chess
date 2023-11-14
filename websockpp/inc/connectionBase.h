#pragma once

#include "wConfig.h"
#include "utils.h"
#include <nlohmann/json.hpp>
#include <semaphore.h>
#include <queue>

using json = nlohmann::json;
/**
 *  This interface indicates functions that have several features supporing communication. 
 *  MOVE From To 
 *  SEL  From
*/

typedef std::function<void (json js)> ConnectionBaseCallback;

class ConnectionBase {
public:

    virtual void run () = 0;
    int send(json const js);
    void setRecvCallback(ConnectionBaseCallback cb);

    virtual int _send(std::string const payload) = 0;
    string _recv(void);
private:
    
protected:
    connection mConnection;
    ConnectionBaseCallback mCallback;
    bool mIsConnected;
    /* temporary for connection established status
    *  because we don't know what mConnection's constructor is
    */
    // endpoint mEndpoint;
    void onOpen(websocketpp::connection_hdl hdl);
    void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg);
    void onClose(websocketpp::connection_hdl hdl);
    void initSem();

};