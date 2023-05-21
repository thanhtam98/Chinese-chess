#include "horseBehaviorProvider.h"
#include "iBoard.h"
#include "iChessman.h"
#include "point.h"
#include <iostream>
bool HorseBehaviorProvider::predicate(Point *point, Rule &rule) {
    return false;
}
void HorseBehaviorProvider::supportHandleFalse(int x, int y, Rule &rule) {
    std::vector<Point*> *possibleMoves = &(rule.possibleMoves);
    IBoard *board = rule.board;
    IChessman *target_chessman = board->getChessman(rule.target);
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
void HorseBehaviorProvider::handleFalse(Point *point, Rule &rule) {
    std::vector<Point*> *possibleMoves = &(rule.possibleMoves);
    IChessman *chessman;
    IBoard *board = rule.board;
    Point* target = rule.target;
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
            supportHandleFalse(stopX+1, stopY+1, rule);
            supportHandleFalse(stopX+1, stopY-1, rule);
            break;
        case NORTH:
            supportHandleFalse(stopX-1, stopY+1, rule);
            supportHandleFalse(stopX+1, stopY+1, rule);
            break;
        case SOUTH:
            supportHandleFalse(stopX-1, stopY-1, rule);
            supportHandleFalse(stopX+1, stopY-1, rule);
            break;
        case WEST:
            supportHandleFalse(stopX-1, stopY+1, rule);
            supportHandleFalse(stopX-1, stopY-1, rule);
            break; 
    default:
        break;
    }
}
