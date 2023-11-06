#pragma once
#include <iostream> 
#include "utils.h"

class ITurn {

public:
    ITurn(team_code team) : 
        nextTurn(nullptr), team(team) {};

    ITurn *setNext(ITurn *handler);
    // int next(void);
    // virtual int handle(void) = 0;
    team_code _getTeam();
    virtual bool _isSatisfiedTurn(team_code this_team) = 0;

    static ITurn *setup(ITurn *first, ITurn * second);
    static ITurn *get(void); 
    static bool isSatisfied(team_code this_team);
    static void end();
    static team_code getTeam();

protected:
    // static I
    static ITurn *curTurn;
    team_code team;
    ITurn *nextTurn;
};

