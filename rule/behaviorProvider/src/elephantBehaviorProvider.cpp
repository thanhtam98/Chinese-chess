#include "elephantBehaviorProvider.h"
#include <vector>
#include "iChessman.h"
#include "iBoard.h"
#include <iostream>
#include <math.h>

bool ElephantBehaviorProvider::predicate(Point *point, Rule &rule) { 
    IBoard *board = rule.board;
    int targetX = rule.target->getX();
    int targetY = rule.target->getY();
    IChessman *targetChessman = board->getChessman(targetX,targetY);
    
    if  (board->isOccupied(point))
    {
        return false;
    }
    Point* target = rule.target;

    int x = point->getX();
    int y = point->getY();

    return !((abs(x-targetX) == 2) && (abs(y-targetY) == 2));
}

/* */
void ElephantBehaviorProvider::handleTrue(Point *point, Rule &rule) {

}

void ElephantBehaviorProvider::handleFalse(Point *point, Rule &rule) {
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    int x = point->getX();
    int y = point->getY();
    int targetX = rule.target->getX();
    int targetY = rule.target->getY();
    IBoard *board = rule.board;
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

vector<direction_code> ElephantBehaviorProvider::getListDir(Rule &rule){
    return {NORTH_WEST,
            NORTH_EAST,
            SOUTH_WEST,
            SOUTH_EAST};
}
