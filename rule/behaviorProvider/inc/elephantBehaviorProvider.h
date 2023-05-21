#pragma once
#include "abstractBehaviorProvider.h"
#include "defaultBehaviorProvider.h"

class ElephantBehaviorProvider : public DefaultBehaviorProvider {
public:
    virtual bool predicate(Point *point, Rule &rule) override;
    virtual void handleTrue(Point *point, Rule &rule) override;
    virtual void handleFalse(Point *point, Rule &rule) override;
    virtual vector<direction_code> getListDir(Rule &rule) override;
};