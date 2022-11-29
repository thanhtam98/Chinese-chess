#pragma once
#include <functional>
#include "rule/rule.h"
#include "rule/abstractRuleBuilder.h"
#include "rule/behaviorProvider/abstractBehaviorProvider.h"

class RuleShapeBuilder : public AbstractRuleBuilder {
private:
    bool isContinuedAndAddPossibleMoves(Point *point, AbstractBehaviorProvider* behaviorProvider);
public:  
    RuleShapeBuilder(Rule &rule) : AbstractRuleBuilder{rule} {};
    RuleLimitBuilder getPlusShape(AbstractBehaviorProvider* behaviorProvider,
                                std::vector<direction_code> denyDirList = {});
    RuleLimitBuilder getCrossShape();
    RuleLimitBuilder getElsShape();
};