#pragma once

#include "wConfig.h"
#include "utils.h"

/**
 *  This interface indicates functions that have several features supporing communication. 
 *  MOVE From To 
 *  SEL  From
*/

class ConnectionBase {
public:
    void sendMsg(int opcode, Point from, Point to);
    void sendMsg(int opcode, Point from);

    virtual void run () = 0;




private:
    virtual int _send(std::string const payload) = 0;
    int send(std::string const payload);
    
protected:
    connection mConnection;
    bool mIsConnected;
    /* temporary for connection established status
    *  because we don't know what mConnection's constructor is
    */
    // endpoint mEndpoint;
    void onOpen(websocketpp::connection_hdl hdl, server::message_ptr msg);
    void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg);
    void onClose(websocketpp::connection_hdl hdl);


};