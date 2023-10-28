#include "chessman.h"
#include "iBoard.h"
#include "board.h"
#include "rule.h"
#include "ruleTargetBuilder.h"
#include "ruleShapeBuilder.h"
#include <ostream>

IChessman* Chessman::newInstance(Piece piece, Point *point) {
    return new Chessman(piece, point);
}

std::vector<Point*> Chessman::getPossibleMoves(){
    IBoard *board = Board::getInstance();
    Rule rule = Rule::create(board).at(slot).getShape();
    // return vector<Point*> {};
    return *rule.getPossibleMove();
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
string Chessman::getName(){
    return piece.getChessmanName();
}
bool Chessman::move(Point* new_point){
    if (new_point == slot)
        return false;
    
    /* Can move the chessman */
    this->slot = new_point;
    return true;
}

std::ostream& operator<<(std::ostream &os,  IChessman &obj)
{
    os << obj.piece.getName();
    return os;
}