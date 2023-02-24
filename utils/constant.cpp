#include "utils/constant.h"

string chessman_name[TEAM_SIZE][CHESSMAN_SIZE] = 
{
    {"將", "士", "象", "馬", "車", "砲", "卒"},
    {"帥", "仕", "相", "傌", "俥", "炮", "兵"}
};

bool Piece::operator!=(const struct Piece& other) {
    return (this->c != other.c) && (this->t != other.t);
}