#pragma once
#include "defaultBehaviorProvider.h"

class GeneralBehaviorProvider : public DefaultBehaviorProvider {
public:
    virtual bool predicate(Point *point, Rule &rule) override;
    virtual void handleFalse(Point *point, Rule &rule) override;

};