#pragma once

#include "wConfig.h"
#include "connectionBase.h"

enum  trans_code {
    MOV,
    SEL,

    TOTAL_CODE
};


class transfer{

    public:
        transfer(ConnectionBase *connection);
        void setConnection(ConnectionBase *connection);
        void sendMsg(trans_code opcode, Point *from, Point *to);
        void sendMsg(trans_code opcode, Point *from);
        // trans_code recvMsg()
    private:
        ConnectionBase *mConnection;

};