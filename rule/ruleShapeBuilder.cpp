#include "rule/ruleShapeBuilder.h"
#include "rule/ruleLimitBuilder.h"
#include "rule/behaviorProvider/abstractBehaviorProvider.h"
#include "utils/constant.h"
#include "utils/utils.h"
#include <iostream>

bool RuleShapeBuilder::isContinuedAndAddPossibleMoves(Point *point,
                    AbstractBehaviorProvider* behaviorProvider)
{
    if (behaviorProvider->predicate(point, rule))
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
RuleLimitBuilder RuleShapeBuilder::getPlusShape(AbstractBehaviorProvider* behaviorProvider,
                                                std::vector<direction_code> denyDirList){

    behaviorProvider->handleDirection(rule);
    
    return RuleLimitBuilder{rule};
}

RuleLimitBuilder RuleShapeBuilder::getCrossShape() {
    Point* target = rule.target;
    int x = target->getX();
    int y = target->getY();
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    for (int i = x+1, j = y+1; i < BOARD_WIDTH && j < BOARD_LENGTH; i++, j++) {
        possibleMoves->push_back(Point::of(i, j));   
    }
    for (int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) {
        possibleMoves->push_back(Point::of(i, j));
    }
    for (int i = x+1, j = y-1; i < BOARD_WIDTH && j >= 0; i++, j--) {
        possibleMoves->push_back(Point::of(i, j));
    }
    for (int i = x-1, j = y+1; i >= 0 && j < BOARD_LENGTH; i--, j++) {
        possibleMoves->push_back(Point::of(i, j));
    }

    return RuleLimitBuilder{rule};
}

RuleLimitBuilder RuleShapeBuilder::getElsShape() {
    Point* target = rule.target;
    int x = target->getX();
    int y = target->getY();
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    
    if (Point::isWithinBoundary(x+1, y+2)) possibleMoves->push_back(Point::of(x+1, y+2));
    if (Point::isWithinBoundary(x+1, y-2)) possibleMoves->push_back(Point::of(x+1, y-2));
    if (Point::isWithinBoundary(x-1, y+2)) possibleMoves->push_back(Point::of(x-1, y+2));
    if (Point::isWithinBoundary(x-1, y-2)) possibleMoves->push_back(Point::of(x-1, y-2));
    if (Point::isWithinBoundary(x+2, y+1)) possibleMoves->push_back(Point::of(x+2, y+1));
    if (Point::isWithinBoundary(x+2, y-1)) possibleMoves->push_back(Point::of(x+2, y-1));
    if (Point::isWithinBoundary(x-2, y+1)) possibleMoves->push_back(Point::of(x-2, y+1));
    if (Point::isWithinBoundary(x-2, y-1)) possibleMoves->push_back(Point::of(x-2, y-1));
    
    return RuleLimitBuilder{rule};
}