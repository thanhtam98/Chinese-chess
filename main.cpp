#include <iostream>
#include "ui/ui.h"
#include "utils/constant.h"
#include "utils/point.h"
#include "rule/rule.h"
#include "logic/iBoard.h"
#include "logic/board.h"

using namespace std;

int main(void)
{
    cout << "Hello woasdasdasrld " << endl;
    IBoard* board = Board::getInstance();

    Point *point = Point::of(2,3);
    // Rule rule = Rule::create(board).at(point).getShape();
    // 
    cout << *point ;
    cout << "end of main " << endl;
}
