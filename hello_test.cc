#include <gtest/gtest.h>
#include <iostream>
#include "ui/ui.h"
#include "utils/constant.h"
#include "utils/point.h"
#include "rule/rule.h"
#include "rule/ruleLimitBuilder.h"
#include "rule/ruleShapeBuilder.h"
#include "rule/ruleTargetBuilder.h"


// Demonstrate some basic assertions.
TEST(PointTest, reusePointAdress) {
  // Expect two strings not to be equal.
  Point* point1 = Point::of(2, 3);
  Point* point2 = Point::of(8, 9);
  // Expect equality.
  EXPECT_EQ(Point::of(2, 3), point1);
  EXPECT_EQ(Point::of(8, 9), point2); 
}