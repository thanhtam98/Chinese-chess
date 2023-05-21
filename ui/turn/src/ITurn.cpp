#include "ITurn.h"

ITurn* ITurn::curTurn = nullptr;

ITurn* ITurn::setNext(ITurn* next){
    this->nextTurn = next;
    return next;
}

// int ITurn::next(void) {
//     if (this->nextTurn) {
//       return this->nextTurn->handle();
//     }
//     return 0;
// }

ITurn* ITurn::setupTurns(ITurn *first, ITurn * second){
    first->setNext(second);
    second->setNext(first);
    return curTurn = first;
}

ITurn* ITurn::getTurn(void) {
    return curTurn;
}

void ITurn::endTurn() {
    curTurn = curTurn->nextTurn;
}

bool ITurn::isSatisfiedTurn(team_code this_team) {
    return getTurn()->_isSatisfiedTurn(this_team);
}

team_code ITurn::getTeam() {
    return curTurn->_getTeam();
}

team_code ITurn::_getTeam() {
    return team;
}