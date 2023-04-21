#include "ui/turn/ITurn.h"

ITurn* ITurn::setNext(ITurn* next){
    this->nextTurn = next;
    return next;
}

int ITurn::next(void) {
    if (this->nextTurn) {
      return this->nextTurn->handle();
    }
    return;
}

ITurn* ITurn::setupTurns(ITurn *first, ITurn * second){
    first->setNext(second);
    second->setNext(first);
    return first;
}