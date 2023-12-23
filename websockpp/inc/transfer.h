#pragma once

#include "wConfig.h"
#include "connectionBase.h"

enum  trans_code {
    MOV,
    SEL,

    TOTAL_CODE
};

typedef std::function<void(Point* from, Point* to)> MovCallback_t;
typedef std::function<void(Point* from)> SelCallback_t;

class Transfer{

    public:
        Transfer(ConnectionBase *connection);
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