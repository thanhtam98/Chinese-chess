#pragma once
#include <vector>

#include "iChessman.h"
#include "utils.h"

class IChessman;

class IBoard {
public:
    virtual bool isOccupied (int x, int y) = 0;
    virtual bool isOccupied (Point *point) = 0;
    virtual IChessman* getChessman(int x, int y) = 0;
    virtual IChessman* getChessman(Point *point) = 0;
    virtual void move(Point* from, Point* to) = 0;
    virtual std::vector<Point*> getPossibleMoves(Point* target) = 0;
    virtual Point* getGeneralLocation(team_code team) = 0;
    virtual void setGeneralLocation(team_code team, Point* location)  = 0;
    virtual void endGame(team_code winningTeam) = 0;
protected:
    /* A map showing all chessmen on the board and where they are */
    IChessman* map[BOARD_WIDTH][BOARD_LENGTH];
    bool isGameOver = false;
    team_code winningTeam;
};