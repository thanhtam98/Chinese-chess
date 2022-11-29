#include "rule/behaviorProvider/cannonBehaviorProvider.h"
#include <vector>
#include <iostream>
#include "logic/iChessman.h"
#include "logic/iBoard.h"

bool CannonBehaviorProvider::predicate(Point *point, Rule &rule) {
    IBoard *board = rule.getIBoard();
    return !board->isOccupied(point->getX(), point->getY());
}

void CannonBehaviorProvider::handleFalse(Point *point, Rule &rule) {
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    IChessman *chessman;
    IBoard *board = rule.board;
    Point* target = rule.target;
    int targetX = target->getX();
    int targetY = target->getY();
    IChessman *targetChessman = board->getChessman(targetX,targetY);

    int stopX = point->getX();
    int stopY = point->getY();
    direction_code dir ;
    
    if (targetX == stopX)
        dir = (targetY > stopY) ? DOWN : UP;
    if (targetY == stopY)
        dir = (targetX > stopX) ? LEFT : RIGHT;
    
    changeForDirection(dir, stopX,stopY);
    while (Point::isWithinBoundary(stopX,stopY)){
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
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y++;
            break;
        case DOWN:
            y--;
            break;    
        default:
            std::cout << "Throw exception " << std::endl;
            break;
    }
}