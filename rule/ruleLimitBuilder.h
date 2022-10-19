#pragma once
#include "rule/rule.h"
#include "rule/abstractRuleBuilder.h"

class RuleLimitBuilder : public AbstractRuleBuilder {
private:
public:
    RuleLimitBuilder(Rule &rule) : AbstractRuleBuilder{rule} {};
};