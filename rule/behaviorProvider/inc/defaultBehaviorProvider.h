#pragma once
#include "abstractBehaviorProvider.h"

class DefaultBehaviorProvider : public AbstractBehaviorProvider {
public:
    DefaultBehaviorProvider(Rule& rule): AbstractBehaviorProvider{rule} {};

    virtual bool predicate(Point *point) override;
    virtual void handleTrue(Point *point) override;
    virtual void handleFalse(Point *point) override;
    virtual void handleBefore() override;
    virtual void handleAfter() override;
    virtual vector<direction_code> getListDir() override;
};