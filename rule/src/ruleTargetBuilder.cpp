#include "ruleTargetBuilder.h"
#include "ruleShapeBuilder.h"

RuleShapeBuilder RuleTargetBuilder::at(Point *point) {
    rule.target = point;
    return RuleShapeBuilder{rule};
}