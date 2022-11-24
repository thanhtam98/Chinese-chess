#include <gtest/gtest.h>
#include <iostream>
#include "test/testUtils.h"
#include "ui/ui.h"
#include "utils/constant.h"
#include "utils/point.h"
#include "rule/rule.h"
#include "rule/ruleLimitBuilder.h"
#include "rule/ruleShapeBuilder.h"
#include "rule/ruleTargetBuilder.h"
#include "logic/iBoard.h"

TEST(PointTest, reusePointAdress) {
  Point* point1 = Point::of(2, 3);
  Point* point2 = Point::of(8, 9);

  EXPECT_EQ(Point::of(2, 3), point1);
  EXPECT_EQ(Point::of(8, 9), point2); 
}

TEST(PointTest, withinPalace) {

  EXPECT_EQ(Point::isWithinPalace(4, 1), true);
  EXPECT_EQ(Point::isWithinPalace(3, 7), true);
  EXPECT_EQ(Point::isWithinPalace(5, 0), true);
  EXPECT_EQ(Point::isWithinPalace(4, 9), true);
  EXPECT_EQ(Point::isWithinPalace(4, 6), false);
  EXPECT_EQ(Point::isWithinPalace(6, 6), false);
  EXPECT_EQ(Point::isWithinPalace(2, 0), false);
  EXPECT_EQ(Point::isWithinPalace(2, 8), false);


}


TEST(PointTest, throwException)
{
  TEST_DESCRIPTION("Test Exception for Point with negative x");
  EXPECT_THROW({
      try
      {
          Point* point1 = Point::of(-1, 3);
      }
      catch( const std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ("Class Point: Invalid Coordinate", e.what());
          throw;
      }
  }, std::invalid_argument);

  TEST_DESCRIPTION("Test Exception for Point with negative y");
  EXPECT_THROW({
      try
      {
          Point* point1 = Point::of(1, -3);
      }
      catch( const std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ("Class Point: Invalid Coordinate", e.what());
          throw;
      }
  }, std::invalid_argument);

  TEST_DESCRIPTION("Test Exception for Point with out-of-bound x");
  EXPECT_THROW({
      try
      {
          Point* point1 = Point::of(BOARD_WIDTH, 3);
      }
      catch( const std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ("Class Point: Invalid Coordinate", e.what());
          throw;
      }
  }, std::invalid_argument);

  TEST_DESCRIPTION("Test Exception for Point with out-of-bound y");
  EXPECT_THROW({
      try
      {
          Point* point1 = Point::of(2, BOARD_LENGTH);
      }
      catch( const std::invalid_argument& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ("Class Point: Invalid Coordinate", e.what());
          throw;
      }
  }, std::invalid_argument);
}