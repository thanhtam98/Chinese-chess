#ifndef __CHESSMAN_H__
#define __CHESSMAN_H__
#include "utils/point.h"
#include <vector>


class IChessman {
public:
    virtual std::vector <Point*> getPossibleMoves() = 0;
    virtual bool move(Point* point) = 0;
    virtual team_code getTeam() = 0;
private:
    Point* slot;
    team_code team;
};
#endif