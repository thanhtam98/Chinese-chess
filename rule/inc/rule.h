#pragma once
#include <vector>
#include "point.h"
#include "iBoard.h"
#include "iChessman.h"

class RuleShapeBuilder;
class RuleTargetBuilder;
class RuleLimitBuilder;
class DefaultBehaviorProvider;
class CannonBehaviorProvider;
class SoldierBehaviorProvider;
class AdvisorBehaviorProvider;
class ElephantBehaviorProvider;
class GeneralBehaviorProvider;
class HorseBehaviorProvider;
/**
 *  @brief 
 *  rule work as a service to provide a set of moves of a chessman.
 *  rule will ask the board for the chessman information
*/
class Rule
{
public:
    // friend class RuleBuilder;
    friend class RuleTargetBuilder;
    friend class RuleShapeBuilder;
    friend class RuleLimitBuilder;
    friend class DefaultBehaviorProvider;
    friend class CannonBehaviorProvider;
    friend class SoldierBehaviorProvider;
    friend class AdvisorBehaviorProvider;
    friend class ElephantBehaviorProvider;
    friend class GeneralBehaviorProvider;
    friend class HorseBehaviorProvider;
    static RuleTargetBuilder create(IBoard *_board);
    friend std::ostream& operator<<(std::ostream &os, const Rule &obj);
    Point* getTarget();
    vector<Point*> getPossibleMove();
    IBoard* getIBoard();
private:
    Point* target;
    vector<Point*> possibleMoves;
    IBoard* board;
};