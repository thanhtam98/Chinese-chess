#pragma once
#include "rule/behaviorProvider/defaultBehaviorProvider.h"

class ChariotBehaviorProvider : public DefaultBehaviorProvider {
public:
    virtual bool predicate(Point *point, Rule &rule) override;
    // virtual void handleTrue(Point *point, Rule &rule) override;
    // virtual void handleFalse(Point *point, Rule &rule) override;
};