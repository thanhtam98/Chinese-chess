#pragma once
#include "abstractBehaviorProvider.h"
#include "defaultBehaviorProvider.h"

class ElephantBehaviorProvider : public DefaultBehaviorProvider {
public:
    ElephantBehaviorProvider(Rule& rule): DefaultBehaviorProvider(rule) {};

    virtual bool predicate(Point *point) override;
    virtual void handleTrue(Point *point) override;
    virtual void handleFalse(Point *point) override;
    virtual vector<direction_code> getListDir() override;
};