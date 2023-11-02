#include "ruleShapeBuilder.h"
#include "abstractBehaviorProvider.h"
#include "utils.h"
#include <iostream>


RuleShapeBuilder RuleShapeBuilder::getShape(){
    Point* target = rule.getTarget();
    vector<Point*> *possibleMoves = rule.getPossibleMove();
    int x = target->getX();
    int y = target->getY();
    IBoard *board = rule.getIBoard();
    IChessman *chessman = board->getChessman(x, y);
    AbstractBehaviorProvider* behaviorProvider = 
        AbstractBehaviorProvider::newInstance(rule, chessman->getCode());

    behaviorProvider->handleDirection();

  
    return *this;
}