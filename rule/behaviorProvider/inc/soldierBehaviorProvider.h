#pragma once
#include "defaultBehaviorProvider.h"

class SoldierBehaviorProvider : public DefaultBehaviorProvider {
public:
    virtual bool predicate(Point *point, Rule &rule) override;
    vector<direction_code> getListDir(Rule &rule) override;    
};