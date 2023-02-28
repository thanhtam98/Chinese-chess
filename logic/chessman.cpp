#include "logic/chessman.h"
#include "logic/iBoard.h"
#include "logic/board.h"
#include "rule/rule.h"
#include "rule/ruleTargetBuilder.h"
#include "rule/ruleLimitBuilder.h"
#include "rule/ruleShapeBuilder.h"

IChessman* Chessman::newInstance(Piece piece, Point *point) {
    return new Chessman(piece, point);
}

std::vector<Point*> Chessman::getPossibleMoves(){
    IBoard *board = Board::getInstance();
    Rule rule = Rule::create(board).at(slot).getShape();
    // return vector<Point*> {};
    return rule.getPossibleMove();
}
Chessman::Chessman(Piece piece, Point *point){
    this->piece = piece;
    this->slot = point;
}
team_code Chessman::getTeam(){
    return piece.t;
}
chessman_code Chessman::getCode(){
    return piece.c;
}
bool Chessman::move(Point* new_point){
    if (new_point == slot)
        return false;
    
    /* Can move the chessman */
    // change slot
    this->slot = new_point;
    return true;
}