#pragma once
#include "rule/behaviorProvider/abstractBehaviorProvider.h"

class DefaultBehaviorProvider : public AbstractBehaviorProvider {
public:
    virtual bool predicate(Point *point, Rule &rule) override;
    virtual void handleTrue(Point *point, Rule &rule) override;
    virtual void handleFalse(Point *point, Rule &rule) override;
    virtual vector<direction_code> getListDir() override;
};