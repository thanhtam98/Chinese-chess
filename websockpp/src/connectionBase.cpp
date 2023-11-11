#include "connectionBase.h"


int ConnectionBase::send(json js){
    
    string payload = js.dump();
    cout <<" Sending" <<payload << endl;
    /* Futher modification for payload  */
    return  _send(payload);    
}

// int ConnectionBase::send(std::string const payload){

//     /* Futher modification for payload  */
//     return  _send(payload);    

// }
string ConnectionBase::_recv(){

    sem_wait(&sem);

    string ret =  recvList.front();
    recvList.pop();

    return ret;
}
json ConnectionBase::recv(){

    string payload = _recv();
    return json::parse(payload);
}
string ConnectionBase::recv(int time ){

    // int error =sem_timedwait(&sem, time);

    string ret =  recvList.front();
    recvList.pop();

    return ret;
}
void ConnectionBase::onOpen(websocketpp::connection_hdl hdl){
    mIsConnected = true;
    mConnection = hdl;
    cout << "onOpen" << endl;

}
void ConnectionBase::onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg){

    sem_post(&sem);
    recvList.push(msg->get_payload());
    // cout << "onMessage" << msg->get_payload() << endl;

}
void ConnectionBase::onClose(websocketpp::connection_hdl hdl){
    mIsConnected = false;
    // mConnection = nullptr;
    cout << "onClose" << endl;

}

void ConnectionBase::initSem(){
    sem_init(&sem, 0, 0);
}