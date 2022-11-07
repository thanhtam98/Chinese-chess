#pragma once
#include <functional>
#include "rule/rule.h"
#include "rule/abstractRuleBuilder.h"

class RuleShapeBuilder : public AbstractRuleBuilder {
private:
    void getPlusShapeHelper(Point *point,std::function<bool(Point *point)> predicate);
public:
    RuleShapeBuilder(Rule &rule) : AbstractRuleBuilder{rule} {};
    RuleLimitBuilder getPlusShape(std::function<bool(Point *point)> predicate);
    RuleLimitBuilder getCrossShape();
    RuleLimitBuilder getElsShape();
};