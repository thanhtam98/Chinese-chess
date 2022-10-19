#pragma once
#include "rule/rule.h"
#include "rule/abstractRuleBuilder.h"

class RuleTargetBuilder : public AbstractRuleBuilder {
private:
    Rule rule;
public:
    RuleTargetBuilder() : AbstractRuleBuilder{rule} {};
    RuleShapeBuilder at(Point *point);
};