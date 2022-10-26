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
TEST(RuleTest, testCrossShape) {
  EXPECT_EQ(4, 2+2);
}