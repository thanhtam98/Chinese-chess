#pragma once
#include <iostream> 
#include "utils.h"
#include <functional>

class ITurn {

public:
    ITurn(team_code team) : nextTurn(nullptr), team(team) {};

    ITurn *setNext(ITurn *handler);
    team_code _getTeam();
    virtual bool _isSatisfiedTurn(team_code this_team) = 0;

    static std::function<void(void)> setupHook;

    static ITurn *setup(ITurn *first, ITurn * second);
    static ITurn *get(void); 
    static ITurn *getOpposite();
    static bool isSatisfied(team_code this_team);
    static void end();
    static team_code getTeam();
    static ITurn* newDebugTurns();
    static ITurn* newOnlineTurns(bool isRedGoingFirst = true);
    static ITurn* newOfflineTurns(bool isRedGoingFirst = true);
    static turn_mode getMode();

protected:
    // static I
    static void clearTurns();
    static turn_mode mode;

    static ITurn *curTurn;
    team_code team;
    ITurn *nextTurn;
};

