#ifndef __CHESSMAN_H__
#define __CHESSMAN_H__
#include "utils/point.h"

class IChessman {
public:
    Point* getPossibleMoves();
    bool move();
private:
    Point* slot;
};
#endif