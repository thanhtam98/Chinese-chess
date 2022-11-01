#pragma once
#include "logic/iChessman.h"
#include "utils/point.h"

class IBoard {
public:
//    virtual std::vector<Point*> get() = 0;
    virtual bool isOccupied (int x, int y) = 0;
    virtual IChessman* getChessman(int x, int y) = 0;

private:
   IChessman* map[BOARD_WIDTH][BOARD_LENGTH];
};