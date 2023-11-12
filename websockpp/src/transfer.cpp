#include "transfer.h"

transfer::transfer(ConnectionBase *connection){
    mConnection = connection;
}

void transfer::setConnection(ConnectionBase *connection){
    mConnection = connection;
}


void transfer::sendMsg(trans_code opcode, Point* from, Point* to){

    json js;

    js["opcode"] = opcode;
    if (from != nullptr)
        js["from"] = {from->getX(), from->getY(), from->getTeam()};
    if (to != nullptr)
        js["to"] = {to->getX(), to->getY(), to->getTeam()};

    mConnection->send(js);
}

void transfer::sendMsg(trans_code opcode, Point* from){

    json js;

    js["opcode"] = opcode;
    if (from != nullptr)
        js["from"] = {from->getX(), from->getY(), from->getTeam()};

    mConnection->send(js);
}
