#pragma once

#include "wConfig.h"
#include "connectionBase.h"

enum  trans_code {
    MOV,
    SEL,

    TOTAL_CODE
};

typedef void (*MovCallback_t)(Point* from, Point* to);
typedef void (*SelCallback_t)(Point* from);

class transfer{

    public:
        transfer(ConnectionBase *connection);
        void setConnection(ConnectionBase *connection);
        void sendMsg(trans_code opcode, Point *from, Point *to);
        void sendMsg(trans_code opcode, Point *from);
        void setCallback(MovCallback_t mcb, SelCallback_t scb);
        void dispatchMsg(json js);
    private:
        ConnectionBase *mConnection;
        MovCallback_t mMovCallback;
        SelCallback_t mSelCallback;
};