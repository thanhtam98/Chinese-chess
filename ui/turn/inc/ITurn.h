#pragma once
#include <iostream> 
#include "constant.h"

class ITurn {

public:
    ITurn(team_code team) : 
        nextTurn(nullptr), team(team) {};

    ITurn *setNext(ITurn *handler);
    // int next(void);
    // virtual int handle(void) = 0;
    team_code _getTeam();
    virtual bool _isSatisfiedTurn(team_code this_team) = 0;

    static ITurn *setupTurns(ITurn *first, ITurn * second);
    static ITurn *getTurn(void); 
    static bool isSatisfiedTurn(team_code this_team);
    static void endTurn();
    static team_code getTeam();

protected:
    // static I
    static ITurn *curTurn;
    team_code team;
    ITurn *nextTurn;
};

