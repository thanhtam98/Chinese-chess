#ifndef __RULE_ABSTRACT_BUILDER_H__
#define __RULE_ABSTRACT_BUILDER_H__
#include "rule.h"
#include <vector>
#include "utils.h"

class AbstractRuleBuilder
{
protected:
    Rule &rule;
    explicit AbstractRuleBuilder(Rule &_rule) : rule{_rule} {};
public:
    operator Rule() const
    {
        return std::move(rule);
    };
};


#endif