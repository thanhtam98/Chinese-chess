#include "ITurn.h"
#include "debugTurn.h"
#include "offlineTurn.h"
#include "onlineTurn.h"

ITurn* ITurn::curTurn = nullptr;

std::function<void(void)> ITurn::setupHook = []{ LOG_F("Init hook") };

ITurn* ITurn::setNext(ITurn* next){
    this->nextTurn = next;
    return next;
}

ITurn* ITurn::setup(ITurn *first, ITurn * second) {
    first->setNext(second);
    second->setNext(first);
    setupHook();
    return curTurn = first;
}

ITurn* ITurn::get(void) {
    return curTurn;
}
ITurn* ITurn::getOpposite(){
    return curTurn->nextTurn;
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

ITurn* ITurn::newDebugTurns() {
    clearTurns();
    ITurn* debugTurn = new DebugTurn();
    return setup(debugTurn, debugTurn);
}

ITurn* ITurn::newOnlineTurns(bool isRedGoingFirst) {
    clearTurns();
    ITurn* redTurn = new OnlineTurn(RED);
    ITurn* blackTurn = new OnlineTurn(BLACK);
    ITurn* firstTurn = isRedGoingFirst ? redTurn : blackTurn;
    ITurn* secondTurn = isRedGoingFirst ? blackTurn : redTurn;
    return setup(firstTurn, secondTurn);
}

ITurn* ITurn::newOfflineTurns(bool isRedGoingFirst) {
    clearTurns();
    ITurn* redTurn = new OfflineTurn(RED);
    ITurn* blackTurn = new OfflineTurn(BLACK);
    ITurn* firstTurn = isRedGoingFirst ? redTurn : blackTurn;
    ITurn* secondTurn = isRedGoingFirst ? blackTurn : redTurn;
    return setup(firstTurn, secondTurn);
}

void ITurn::clearTurns() {
    if (curTurn == nullptr) {
        return;
    }
    ITurn* next = curTurn->nextTurn;
    if (next != curTurn) {
        delete curTurn;
    }
    delete next;
}