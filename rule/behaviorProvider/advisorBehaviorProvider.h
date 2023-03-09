#pragma once
#include "rule/behaviorProvider/abstractBehaviorProvider.h"
#include "rule/behaviorProvider/defaultBehaviorProvider.h"

class AdvisorBehaviorProvider : public DefaultBehaviorProvider {
public:
    virtual bool predicate(Point *point, Rule &rule) override;
    virtual void handleTrue(Point *point, Rule &rule) override;
    virtual void handleFalse(Point *point, Rule &rule) override;
    virtual vector<direction_code> getListDir(Rule &rule) override;
};