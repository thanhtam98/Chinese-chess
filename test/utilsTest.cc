#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>

#include "utils/point.h"
#include "utils/utils.h"
#include "rule/rule.h"
#include "rule/ruleLimitBuilder.h"
#include "rule/ruleShapeBuilder.h"
#include "rule/ruleTargetBuilder.h"
#include "test/mockBoard.h"

void listPointCmp(vector<Point *> expect, vector<Point *> actual)
{
  EXPECT_EQ(expect.size(), actual.size());

  for (Point *i : expect)
  {
    EXPECT_NE(std::find(actual.begin(),
                        actual.end(), i),
              actual.end())
        << "[----------] Expect: ["
        << i->getX() << "," << i->getY() << "]. But not found" << endl;
  }
}


TEST(RuleTest, testRemovePointFromVector)
{
  vector<Point *> input = {
      Point::of(7, 1),
      Point::of(6, 2),
      Point::of(5, 3),
      Point::of(4, 4),
      Point::of(3, 5),
      Point::of(2, 6),
      Point::of(1, 7),
      Point::of(0, 8)};
      
  vector<Point *> expect = {
      Point::of(7, 1),
      Point::of(5, 3),
      Point::of(4, 4),
      Point::of(3, 5),
      Point::of(2, 6),
      Point::of(1, 7),
      Point::of(0, 8)};

  Utils::removePointFromVector(&input, 6 ,2 );
  listPointCmp(expect, input);
}