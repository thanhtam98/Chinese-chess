#include "rule/rule.h"
#include "rule/ruleTargetBuilder.h"
#include <string>
#include <iostream>

RuleTargetBuilder Rule::create(IBoard *_board) {
    // board = _board;
    return RuleTargetBuilder{_board};
}
Point* Rule::getTarget()
{
    return target;
}
vector<Point*> Rule::getPossibleMove(){
    return possibleMoves;
}
IBoard* Rule::getIBoard(){
    return board;
}

std::ostream& operator<<(std::ostream &os, const Rule &obj)
{
    os << "from: [" << obj.target->getX() << ","
                   << obj.target->getY() << "] to: ";
    for (Point *p: obj.possibleMoves)
        os << " [" << p->getX() <<"," << p->getY() << "] ";
    os << endl;
    return os;
}
// std::ostream& operator<<(std::ostream &os, const string sa)
// {
//     return os << sa;
// }

// cout << Rule << "Dasdfasdf";

