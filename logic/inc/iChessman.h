#ifndef __CHESSMAN_H__
#define __CHESSMAN_H__
#include <vector>
#include "utils.h"
#include "iBoard.h"
/**
 * @brief indicate all information about a chessman.
*/
class IBoard;
class IChessman {
public:
    virtual std::vector <Point*> getPossibleMoves() = 0;
    virtual std::vector <Point*> getPossibleMoves(IBoard* board) = 0;
    virtual bool move(Point* point) = 0; // provide for Iboard
    virtual team_code getTeam() = 0; // 
    virtual chessman_code getCode() = 0; //
    virtual string getName() = 0; //
    static IChessman* newInstance(Piece piece, Point *point);
    friend std::ostream& operator<<(std::ostream &os,  IChessman &obj);
protected:
    // vector <Point*> possibleMoves; // store the possible moves
    Point* slot;
    Piece  piece;
};
#endif