#pragma once
#include "defaultBehaviorProvider.h"

class HorseBehaviorProvider : public DefaultBehaviorProvider {
public:
    HorseBehaviorProvider(Rule& rule): DefaultBehaviorProvider(rule) {};

    virtual bool predicate(Point *point) override;
    virtual void handleFalse(Point *point) override;
private:
    void supportHandleFalse(int x, int y);
};