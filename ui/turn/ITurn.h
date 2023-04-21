#include <iostream> 
#include "utils/constant.h"
#include "ui/boardDiaglog.h"

class ITurn {

public:
    ITurn(team_code team, BoardDialog *board) : 
        nextTurn(nullptr),team(team),board(board){};

    ITurn *setNext(ITurn *handler);
    int next(void);
    virtual int handle(void) = 0;

    static ITurn *setupTurns(ITurn *first, ITurn * second);
    static ITurn *getTurn(void); 

private:
    // static I
    BoardDialog *board;
    team_code team;
    ITurn *nextTurn;
};

