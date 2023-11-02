#include "horseBehaviorProvider.h"
#include "iBoard.h"
#include "iChessman.h"
#include "utils.h"
#include <iostream>
bool HorseBehaviorProvider::predicate(Point *point) {
    return false;
}
void HorseBehaviorProvider::supportHandleFalse(int x, int y) {
    std::vector<Point*> *possibleMoves = rule.getPossibleMove();
    IBoard *board = rule.getIBoard();
    IChessman *target_chessman = board->getChessman(rule.getTarget());
    // cout << "x " << x << " y " << y << endl;
    if (!Point::isWithinBoundary(x,y))
        return;
    if (!board->isOccupied(x, y)){
        possibleMoves->push_back(Point::of(x, y));
    }
    else{
        IChessman *chessman = board->getChessman(Point::of(x, y));
        if (chessman->getTeam() != target_chessman->getTeam())
            possibleMoves->push_back(Point::of(x, y));
    }
    
}
void HorseBehaviorProvider::handleFalse(Point *point) {
    std::vector<Point*> *possibleMoves = rule.getPossibleMove();
    IChessman *chessman;
    IBoard *board = rule.getIBoard();
    Point* target = rule.getTarget();
    int x = target->getX();
    int y = target->getY();

    int stopX = point->getX();
    int stopY = point->getY();
    direction_code dir ;

    if (board->isOccupied(point)){
        return;
    }
    if (x == stopX)
        dir = (y > stopY) ? SOUTH : NORTH;
    if (y == stopY)
        dir = (x > stopX) ? WEST : EAST;

    switch (dir)
    {
        case EAST:
            supportHandleFalse(stopX+1, stopY+1);
            supportHandleFalse(stopX+1, stopY-1);
            break;
        case NORTH:
            supportHandleFalse(stopX-1, stopY+1);
            supportHandleFalse(stopX+1, stopY+1);
            break;
        case SOUTH:
            supportHandleFalse(stopX-1, stopY-1);
            supportHandleFalse(stopX+1, stopY-1);
            break;
        case WEST:
            supportHandleFalse(stopX-1, stopY+1);
            supportHandleFalse(stopX-1, stopY-1);
            break; 
    default:
        break;
    }
}
