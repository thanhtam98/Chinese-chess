#pragma once

#include "point.h"
#include "constant.h"
#include <vector>
#include "iChessman.h"
/**
 * @brief indicate all information about a chessman.
*/

class Chessman : public IChessman {
public:
    std::vector <Point*> getPossibleMoves();
    bool move(Point* new_point); // provide for Iboard
    team_code getTeam();
    chessman_code getCode(); 
    string getName(); 
    Chessman(Piece piece, Point *point);
    static IChessman* newInstance(Piece piece, Point *point);
};
