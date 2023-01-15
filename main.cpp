#include <iostream>
#include "ui/ui.h"
#include "utils/constant.h"
#include "utils/point.h"
#include "rule/rule.h"


using namespace std;

int main(void)
{
    cout << "Hello woasdasdasrld " << endl;

    Point *point = Point::of(2,3);
    cout << *point ;
    cout << "end of main " << endl;
}
