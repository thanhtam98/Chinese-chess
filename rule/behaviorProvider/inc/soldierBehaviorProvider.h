#pragma once
#include "defaultBehaviorProvider.h"

class SoldierBehaviorProvider : public DefaultBehaviorProvider {
public:
    SoldierBehaviorProvider(Rule& rule): DefaultBehaviorProvider(rule) {};

    virtual bool predicate(Point *point) override;
    vector<direction_code> getListDir() override;    
};