#pragma once
#include "rule/rule.h"
#include "rule/abstractRuleBuilder.h"
#include "logic/iBoard.h"
class RuleTargetBuilder : public AbstractRuleBuilder {
private:
    Rule rule;
public:
    RuleTargetBuilder(IBoard *_board) : AbstractRuleBuilder{rule} {
            rule.board = _board;
    };
    RuleShapeBuilder at(Point *point);
};