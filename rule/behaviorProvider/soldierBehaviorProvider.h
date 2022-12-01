#pragma once
#include "rule/behaviorProvider/defaultBehaviorProvider.h"

class SoldierBehaviorProvider : public DefaultBehaviorProvider {
public:
    virtual bool predicate(Point *point, Rule &rule) override;
    // vector<direction_code> getListDir() override;    
};