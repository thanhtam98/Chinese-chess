#include "ruleShapeBuilder.h"
#include "abstractBehaviorProvider.h"
#include "constant.h"
#include "utils.h"
#include <iostream>


RuleShapeBuilder RuleShapeBuilder::getShape(){
    Point* target = rule.target;
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    int x = target->getX();
    int y = target->getY();
    IBoard *board = rule.board;
    IChessman *chessman = board->getChessman(x, y);
    AbstractBehaviorProvider* behaviorProvider = 
        AbstractBehaviorProvider::newInstance(chessman->getCode());

    behaviorProvider->handleDirection(rule);

  
    return *this;
}