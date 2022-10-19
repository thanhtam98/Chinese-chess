#pragma once
#include "rule/rule.h"
#include "rule/abstractRuleBuilder.h"

class RuleShapeBuilder : public AbstractRuleBuilder {
private:
public:
    RuleShapeBuilder(Rule &rule) : AbstractRuleBuilder{rule} {};
    RuleLimitBuilder getPlusShape();
    RuleLimitBuilder getCrossShape();
    RuleLimitBuilder getElsShape();
};