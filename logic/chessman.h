#pragma once

#include "utils/point.h"
#include "utils/constant.h"
#include <vector>
#include "logic/iChessman.h"
/**
 * @brief indicate all information about a chessman.
*/

class Chessman : public IChessman {
public:
    std::vector <Point*> getPossibleMoves();
    bool move(Point* new_point); // provide for Iboard
    team_code getTeam();// 
    chessman_code getCode(); //
    Chessman(Piece piece, Point *point);
    static IChessman* newInstance(Piece piece, Point *point);
};
