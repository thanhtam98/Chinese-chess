#pragma once
#include "abstractBehaviorProvider.h"

class DefaultBehaviorProvider : public AbstractBehaviorProvider {
public:
    virtual bool predicate(Point *point, Rule &rule) override;
    virtual void handleTrue(Point *point, Rule &rule) override;
    virtual void handleFalse(Point *point, Rule &rule) override;
    virtual void handleBefore(Rule &rule) override;
    virtual void handleAfter(Rule &rule) override;
    virtual vector<direction_code> getListDir(Rule &rule) override;
};