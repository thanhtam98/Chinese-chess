#pragma once
#include "utils/point.h"
#include "rule/rule.h"

class AbstractBehaviorProvider {
public:
    virtual bool predicate(Point *point, Rule &rule) = 0;
    virtual void handleTrue(Point *point, Rule &rule) = 0;
    virtual void handleFalse(Point *point, Rule &rule) = 0;
};