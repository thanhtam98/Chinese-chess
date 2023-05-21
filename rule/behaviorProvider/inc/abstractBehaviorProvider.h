#pragma once
#include "point.h"
#include "rule.h"
#include "constant.h"
#include "directionIterator.h"

/**
 *  class AbstractBehaviorProvider
 *  @brief provides the behavior of chessman rule
*/

class AbstractBehaviorProvider {
public:
/*
* Function: predicate
* description: return false if we need to change the direction
*/
    virtual bool predicate(Point *point, Rule &rule) = 0;
/*
*  Function: handleTrue
*  description: behavior when predicate returns true
*/
    virtual void handleTrue(Point *point, Rule &rule) = 0;
/*
*  Function: handleFalse
*  description: action when we change the direction (predicate returns false)
*/
    virtual void handleFalse(Point *point, Rule &rule) = 0;
    virtual vector<direction_code> getListDir(Rule &rule) = 0;
    void handleDirection(Rule &rule);

    static AbstractBehaviorProvider* newInstance(chessman_code code);
};