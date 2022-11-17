#pragma once
#include <functional>
#include "rule/rule.h"
#include "rule/abstractRuleBuilder.h"

class RuleShapeBuilder : public AbstractRuleBuilder {
private:
    bool isContinuedAndAddPossibleMoves(Point *point,std::function<bool(Point *point, Rule &rule)> predicate,
                                        std::function<void(Point *point, Rule &rule)> handleTrue, 
                                        std::function<void(Point *point, Rule &rule)> handleFalse);
public:  
    static std::function<void(Point *point, Rule &rule)> defaultHandleTrue;
    static std::function<void(Point *point, Rule &rule)> defaultHandleFalse;
    RuleShapeBuilder(Rule &rule) : AbstractRuleBuilder{rule} {};
    RuleLimitBuilder getPlusShape(std::function<bool(Point *point, Rule &rule)> predicate,
                                std::function<void(Point *point, Rule &rule)> handleTrue, 
                                std::function<void(Point *point, Rule &rule)> handleFalse);
    RuleLimitBuilder getCrossShape();
    RuleLimitBuilder getElsShape();
};