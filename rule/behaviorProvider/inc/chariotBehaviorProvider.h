#pragma once
#include "defaultBehaviorProvider.h"

class ChariotBehaviorProvider : public DefaultBehaviorProvider {
public:
    ChariotBehaviorProvider(Rule& rule): DefaultBehaviorProvider(rule) {};

    virtual bool predicate(Point *point) override;
    // virtual void handleTrue(Point *point, Rule &rule) override;
    // virtual void handleFalse(Point *point, Rule &rule) override;
    
};