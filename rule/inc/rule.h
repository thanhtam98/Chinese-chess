#pragma once
#include <vector>
#include "utils.h"
#include "iBoard.h"
#include "iChessman.h"

class RuleShapeBuilder;
class RuleTargetBuilder;
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
    static RuleTargetBuilder create(IBoard *_board);
    friend std::ostream& operator<<(std::ostream &os, const Rule &obj);
    Point* getTarget();
    vector<Point*> *getPossibleMove();
    IBoard* getIBoard();
private:
    Point* target;
    vector<Point*> possibleMoves;
    IBoard* board;
};