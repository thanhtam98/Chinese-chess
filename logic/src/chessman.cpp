#include "chessman.h"
#include "iBoard.h"
#include "board.h"
#include "rule.h"
#include "ruleTargetBuilder.h"
#include "ruleShapeBuilder.h"
#include <ostream>
#include "log.h"

IChessman* Chessman::newInstance(Piece piece, Point *point) {
    return new Chessman(piece, point);
}

std::vector<Point*> Chessman::getPossibleMoves(){
    IBoard *board = Board::getInstance();
    Rule rule = Rule::create(board).at(slot).getShape();
    // return vector<Point*> {};
    return *rule.getPossibleMove();
}

std::vector<Point*> Chessman::getPossibleMoves(IBoard *board){

    Rule rule = Rule::create(board).at(slot).getShape();
    return *rule.getPossibleMove();
}

Chessman::Chessman(Piece piece, Point *point){
    this->piece = piece;
    this->slot = point;
}

Chessman::~Chessman() {
    LOG_F("Deconstructor");
    if (getCode() == GENERAL) {
        LOG_F("Game ends. Team %s wins.", getTeam() == RED ? "RED" : "BLACK");
        Board::getInstance()->endGame(getTeam() == RED ? BLACK : RED);
    }
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