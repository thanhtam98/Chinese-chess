#pragma once
#include <vector>
#include "utils/point.h"

class RuleShapeBuilder;
class RuleTargetBuilder;
class RuleLimitBuilder;

class Rule
{
public:
    // friend class RuleBuilder;
    friend class RuleTargetBuilder;
    friend class RuleShapeBuilder;
    friend class RuleLimitBuilder;
    static RuleTargetBuilder create();
    friend std::ostream& operator<<(std::ostream &os, const Rule &obj);
    Point* getTarget();
    vector<Point*> getPossibleMove();
private:
    Point* target;
    vector<Point*> possibleMoves;
    // Rule() {};
};


// // Rule::create() .at(Point::of(1,1))
// .getPlusShape()
// .getCrossShape() -> RuleLimitBuilder 
// .getHorseShape()
// >> return type 