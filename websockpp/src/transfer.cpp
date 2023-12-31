#include "transfer.h"

Transfer::Transfer(ConnectionBase *connection){
    mConnection = connection;
    mConnection->setRecvCallback(std::bind(&Transfer::dispatchMsg, this,::_1));

}

void Transfer::setConnection(ConnectionBase *connection){
    mConnection = connection;
    mConnection->setRecvCallback(std::bind(&Transfer::dispatchMsg, this,::_1));

}
void Transfer::setCallback(MovCallback_t mcb, SelCallback_t scb){
    mMovCallback = mcb;
    mSelCallback = scb;
}

void Transfer::sendMsg(trans_code opcode, Point* from, Point* to){

    json js;

    js["opcode"] = opcode;
    if (from != nullptr)
        js["from"] = {from->getX(), from->getY()};
    if (to != nullptr)
        js["to"] = {to->getX(), to->getY()};

    mConnection->send(js);
}

void Transfer::sendMsg(trans_code opcode, Point* from){

    json js;

    js["opcode"] = opcode;
    if (from != nullptr)
        js["from"] = {from->getX(), from->getY()};

    mConnection->send(js);
}

void Transfer::dispatchMsg(json js){
    // cout << "recv" << js.dump(0);
    trans_code code = js["opcode"];
    Point* from = Point::of(js["from"][0], js["from"][1]);
    Point* to;
    switch (code)
    {
    case MOV:
        to = Point::of(js["to"][0], js["to"][1]);
        if (mMovCallback)
            (mMovCallback)(from, to);
        break;
    case SEL:
        if (mSelCallback)
            (mSelCallback)(from);
        break;
    default:
        break;
    }
}