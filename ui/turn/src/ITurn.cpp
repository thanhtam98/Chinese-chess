#include "ITurn.h"

ITurn* ITurn::curTurn = nullptr;

ITurn* ITurn::setNext(ITurn* next){
    this->nextTurn = next;
    return next;
}

ITurn* ITurn::setup(ITurn *first, ITurn * second) {
    first->setNext(second);
    second->setNext(first);
    return curTurn = first;
}

ITurn* ITurn::get(void) {
    return curTurn;
}

void ITurn::end() {
    curTurn = curTurn->nextTurn;
}

bool ITurn::isSatisfied(team_code this_team) {
    return get()->_isSatisfiedTurn(this_team);
}

team_code ITurn::getTeam() {
    return curTurn->_getTeam();
}

team_code ITurn::_getTeam() {
    return team;
}