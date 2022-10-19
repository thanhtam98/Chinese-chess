#include "rule/ruleTargetBuilder.h"
#include "rule/ruleShapeBuilder.h"

RuleShapeBuilder RuleTargetBuilder::at(Point *point) {
    rule.target = point;
    return RuleShapeBuilder{rule};
}