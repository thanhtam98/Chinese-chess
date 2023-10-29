#pragma once
#include "defaultBehaviorProvider.h"
#include "constant.h"

class CannonBehaviorProvider : public DefaultBehaviorProvider {
public:
    CannonBehaviorProvider(Rule& rule): DefaultBehaviorProvider(rule) {};
    virtual bool predicate(Point *point) override;
    // virtual void handleTrue(Point *point, Rule &rule) override;
    virtual void handleFalse(Point *point) override;
private:
    void changeForDirection(direction_code dir, int &x, int  &y);
};