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
    explicit AbstractBehaviorProvider(Rule& rule): rule{rule} {};
/*
* Function: predicate
* description: return false if we need to change the direction
*/
    virtual bool predicate(Point *point) = 0;
/*
*  Function: handleTrue
*  description: behavior when predicate returns true
*/
    virtual void handleTrue(Point *point) = 0;
/*
*  Function: handleFalse
*  description: action when we change the direction (predicate returns false)
*/
    virtual void handleFalse(Point *point) = 0;
/*
*  Function: handleBefore
*  description: behavior before the predicate
*/
    virtual void handleBefore() = 0;
/*
*  Function: handleFalse
*  description: behavior after the predicate
*/
    virtual void handleAfter() = 0;

    virtual vector<direction_code> getListDir() = 0;
    void handleDirection();

    static AbstractBehaviorProvider* newInstance(Rule& rule, chessman_code code);
protected:
    Rule& rule;
};