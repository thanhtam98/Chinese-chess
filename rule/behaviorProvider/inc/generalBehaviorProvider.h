#pragma once
#include "defaultBehaviorProvider.h"

class GeneralBehaviorProvider : public DefaultBehaviorProvider {
public:
    GeneralBehaviorProvider(Rule& rule): DefaultBehaviorProvider(rule) {};

    virtual bool predicate(Point *point) override;
    virtual void handleFalse(Point *point) override;
    virtual void handleAfter() override;
};