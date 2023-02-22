#pragma once
#include "rule/behaviorProvider/defaultBehaviorProvider.h"

class HorseBehaviorProvider : public DefaultBehaviorProvider {
public:
    virtual bool predicate(Point *point, Rule &rule) override;
    virtual void handleFalse(Point *point, Rule &rule) override;
private:
    void supportHandleFalse(int x, int y, Rule &rule);
};