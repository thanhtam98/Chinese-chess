#include "rule/behaviorProvider/soldierBehaviorProvider.h"
#include "logic/iBoard.h"
#include "logic/iChessman.h"
#include "utils/point.h"

bool SoldierBehaviorProvider::predicate(Point *point, Rule &rule) {
    return false;
}

vector<direction_code> SoldierBehaviorProvider::getListDir(Rule &rule) {
    Point* target = rule.getTarget();
    IBoard* board = rule.getIBoard();
    IChessman *chessman = board->getChessman(target->getX(), target->getY());
    team_code team = chessman->getTeam();

    if(chessman == NULL){
        return vector<direction_code>();
    }

    if (target->getTeam() == team) {
        if (team == RED) return {NORTH};
        else return {SOUTH};
    } else {
        if (team == RED) return {NORTH, WEST, EAST};
        else return {SOUTH, WEST, EAST};
    }
}