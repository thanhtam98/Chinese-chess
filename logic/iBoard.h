#pragma once
#include "logic/iChessman.h"
#include "utils/point.h"

class IChessman;

class IBoard {
public:
//    virtual std::vector<Point*> get() = 0;
    virtual bool isOccupied (int x, int y) = 0;
    virtual bool isOccupied (Point *point) = 0;
    virtual IChessman* getChessman(int x, int y) = 0;
    virtual IChessman* getChessman(Point *point) = 0;

protected:
    /* A map showing all chessmen on the board and where they are */
    IChessman* map[BOARD_WIDTH][BOARD_LENGTH];
};