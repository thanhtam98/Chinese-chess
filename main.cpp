#include <iostream>
#include "ui/ui.h"
#include "utils/constant.h"
#include "utils/point.h"
#include "rule/rule.h"
#include "rule/ruleLimitBuilder.h"
#include "rule/ruleShapeBuilder.h"
#include "rule/ruleTargetBuilder.h"

using namespace std;

int main(void)
{
    // cout << "Hello woasdasdasrld " << endl;
    cout << chessman_name[RED][GENERAL] << endl;
    UI::draw();
    Rule rule = Rule::create().at(Point::of(2, 1)).getPlusShape();
    cout << rule;
    Rule rule_a = Rule::create().at(Point::of(2, 1)).getCrossShape();
    cout << rule_a;
    Rule rule_b = Rule::create().at(Point::of(2, 1)).getElsShape();
    cout << rule_b;
    cout << "Nguyen Duy Tan - a 10k bet"
}
