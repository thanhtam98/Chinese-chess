#include <gtest/gtest.h>
#include <iostream>
#include "test/testUtils.h"
#include "ui.h"
#include "utils.h"
#include "rule.h"
#include "ruleShapeBuilder.h"
#include "ruleTargetBuilder.h"
#include "iBoard.h"

TEST(PointTest, reusePointAdress) {
  Point* point1 = Point::of(2, 3);
  Point* point2 = Point::of(8, 9);

  EXPECT_EQ(Point::of(2, 3), point1);
  EXPECT_EQ(Point::of(8, 9), point2); 
}

TEST(PointTest, withinPalace) {

  EXPECT_EQ(Point::of(4, 1)->isWithinPalace(), true);
  EXPECT_EQ(Point::of(3, 7)->isWithinPalace(), true);
  EXPECT_EQ(Point::of(5, 0)->isWithinPalace(), true);
  EXPECT_EQ(Point::of(4, 9)->isWithinPalace(), true);
  EXPECT_EQ(Point::of(4, 6)->isWithinPalace(), false);
  EXPECT_EQ(Point::of(6, 6)->isWithinPalace(), false);
  EXPECT_EQ(Point::of(2, 0)->isWithinPalace(), false);
  EXPECT_EQ(Point::of(2, 8)->isWithinPalace(), false);


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