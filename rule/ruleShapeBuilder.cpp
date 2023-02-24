#include "rule/ruleShapeBuilder.h"
#include "rule/ruleLimitBuilder.h"
#include "rule/behaviorProvider/abstractBehaviorProvider.h"
#include "utils/constant.h"
#include "utils/utils.h"
#include <iostream>


bool RuleShapeBuilder::isContinuedAndAddPossibleMoves(Point *point,
                    AbstractBehaviorProvider* behaviorProvider)
{ if (behaviorProvider->predicate(point, rule))
    {
        behaviorProvider->handleTrue(point, rule);
        return true;
    }
    else
    {
        behaviorProvider->handleFalse(point, rule);
        return false;
    }
}
RuleLimitBuilder RuleShapeBuilder::getShape(){
    Point* target = rule.target;
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    int x = target->getX();
    int y = target->getY();
    IBoard *board = rule.board;
    IChessman *chessman = board->getChessman(x, y);
    AbstractBehaviorProvider* behaviorProvider = 
        AbstractBehaviorProvider::newInstance(chessman->getCode());

    behaviorProvider->handleDirection(rule);

  
    return RuleLimitBuilder{rule};
}