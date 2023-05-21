#pragma once
#include "rule.h"
#include "abstractRuleBuilder.h"
#include "iBoard.h"
class RuleTargetBuilder : public AbstractRuleBuilder {
private:
    Rule rule;
public:
    RuleTargetBuilder(IBoard *_board) : AbstractRuleBuilder{rule} {
            rule.board = _board;
    };
    RuleShapeBuilder at(Point *point);
};