#pragma once
#include <functional>
#include "rule.h"
#include "abstractRuleBuilder.h"
#include "abstractBehaviorProvider.h"

class RuleShapeBuilder : public AbstractRuleBuilder {
private:
    bool isContinuedAndAddPossibleMoves(Point *point, AbstractBehaviorProvider* behaviorProvider);
public:  
    RuleShapeBuilder(Rule &rule) : AbstractRuleBuilder{rule} {};
    RuleLimitBuilder getShape();
};