#include "rule/behaviorProvider/soldierBehaviorProvider.h"
#include "logic/iBoard.h"
#include "logic/iChessman.h"
#include "utils/point.h"

bool SoldierBehaviorProvider::predicate(Point *point, Rule &rule) {
    return false;
}

std::vector<direction_code> SoldierBehaviorProvider::getListDir(Rule &rule){

    Point *point = rule.getTarget();
    IBoard *board = rule.board;
    int x = point->getX();
    int y = point->getY();
    IChessman *chessman = board->getChessman(x,y);

    if(chessman == NULL){
        return vector<direction_code>();
    }

    if (chessman->getTeam() == point->getTeam()){
        if (chessman->getTeam() == RED){
            return {NORTH};
        }
        else{
            return {SOUTH};
        } 
    }
    else{
        if (chessman->getTeam() == RED){
            return {NORTH, EAST, WEST};
        }else{
            return {SOUTH, EAST, WEST};
        }
    }
}
