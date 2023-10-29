#include "elephantBehaviorProvider.h"
#include <vector>
#include "iChessman.h"
#include "iBoard.h"
#include <iostream>
#include <math.h>

bool ElephantBehaviorProvider::predicate(Point *point) { 
    IBoard *board = rule.getIBoard();
    int targetX = rule.getTarget()->getX();
    int targetY = rule.getTarget()->getY();
    IChessman *targetChessman = board->getChessman(targetX,targetY);
    
    if  (board->isOccupied(point))
    {
        return false;
    }
    Point* target = rule.getTarget();

    int x = point->getX();
    int y = point->getY();

    return !((abs(x-targetX) == 2) && (abs(y-targetY) == 2));
}

/* */
void ElephantBehaviorProvider::handleTrue(Point *point) {

}

void ElephantBehaviorProvider::handleFalse(Point *point) {
    vector<Point*> *possibleMoves = rule.getPossibleMove();
    int x = point->getX();
    int y = point->getY();
    int targetX = rule.getTarget()->getX();
    int targetY = rule.getTarget()->getY();
    IBoard *board = rule.getIBoard();
    IChessman *targetChessman = board->getChessman(targetX,targetY);
    
    if (targetChessman->getTeam() != point->getTeam()) 
        return;
    
    if (abs(x-targetX) == 2 && abs(y-targetY) == 2) {
        if  (board->isOccupied(point))
        {
            IChessman *chessman = board->getChessman(point);
            if (chessman->getTeam() != targetChessman->getTeam()){
                possibleMoves->push_back(point);
            }
        }
        else{
            possibleMoves->push_back(point);
        }
    }
}

vector<direction_code> ElephantBehaviorProvider::getListDir(){
    return {NORTH_WEST,
            NORTH_EAST,
            SOUTH_WEST,
            SOUTH_EAST};
}
