#pragma once
#include "rule/behaviorProvider/defaultBehaviorProvider.h"
#include "utils/constant.h"

class CannonBehaviorProvider : public DefaultBehaviorProvider {
public:
    virtual bool predicate(Point *point, Rule &rule) override;
    // virtual void handleTrue(Point *point, Rule &rule) override;
    virtual void handleFalse(Point *point, Rule &rule) override;
private:
    void changeForDirection(direction_code dir, int &x, int  &y);
};