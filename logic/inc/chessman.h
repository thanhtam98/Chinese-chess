#pragma once

#include <vector>
#include "utils.h"
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
    ~Chessman();
    static IChessman* newInstance(Piece piece, Point *point);
};
