#include "rule/rule.h"
#include "rule/ruleTargetBuilder.h"
#include <string>
#include <iostream>

RuleTargetBuilder Rule::create() {
    return RuleTargetBuilder{};
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
