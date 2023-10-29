#include "cannonBehaviorProvider.h"
#include <vector>
#include <iostream>
#include "iChessman.h"
#include "iBoard.h"

bool CannonBehaviorProvider::predicate(Point *point, Rule &rule) {
    IBoard *board = rule.getIBoard();
    return !board->isOccupied(point->getX(), point->getY());
}

void CannonBehaviorProvider::handleFalse(Point *point, Rule &rule) {
    vector<Point*> *possibleMoves = rule.getPossibleMove();
    IChessman *chessman;
    IBoard *board = rule.getIBoard();
    Point* target = rule.getTarget();
    int targetX = target->getX();
    int targetY = target->getY();
    IChessman *targetChessman = board->getChessman(targetX,targetY);

    int stopX = point->getX();
    int stopY = point->getY();
    direction_code dir ;
    
    if (targetX == stopX)
        dir = (targetY > stopY) ? SOUTH : NORTH;
    if (targetY == stopY)
        dir = (targetX > stopX) ? WEST : EAST;
    
    changeForDirection(dir, stopX,stopY);
    while (point->isWithinBoundary()){
        if (board->isOccupied(stopX,stopY))
        {
            chessman = board->getChessman(stopX,stopY);
            if (chessman->getTeam() != targetChessman->getTeam()){
                possibleMoves->push_back(Point::of(stopX,stopY));
            }
            break;
        }
        changeForDirection(dir, stopX,stopY);
    }
}

void CannonBehaviorProvider::changeForDirection(direction_code dir, int &x, int  &y)
{
    switch (dir)
    {
        case WEST:
            x--;
            break;
        case EAST:
            x++;
            break;
        case NORTH:
            y++;
            break;
        case SOUTH:
            y--;
            break;    
        default:
            std::cout << "Throw exception " << std::endl;
            break;
    }
}

