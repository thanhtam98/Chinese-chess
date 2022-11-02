#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>

#include "utils/constant.h"
#include "utils/point.h"
#include "rule/rule.h"
#include "rule/ruleLimitBuilder.h"
#include "rule/ruleShapeBuilder.h"
#include "rule/ruleTargetBuilder.h"
#include "test/mockBoard.h"
#include "test/mockChessman.h"


using ::testing::Return;
using ::testing::AtLeast;

// Demonstrate some basic assertions.
TEST(RuleTest, testTargetBuilder)
{
  MockBoard board;
  Rule rule = Rule::create(&board).at(Point::of(1, 2));
  EXPECT_EQ(Point::of(1, 2), rule.getTarget());
}
void listPossibleMoveCmp(vector<Point *> expect, vector<Point *> actual)
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

TEST(RunTest, testGetPlusShapeCase1)
{
  MockBoard board;
  vector<Point *> expect = {
      Point::of(4, 0),
      Point::of(4, 1),
      Point::of(4, 2),
      Point::of(4, 4),
      Point::of(4, 5),
      Point::of(4, 6),
      Point::of(4, 7),
      Point::of(4, 8),
      Point::of(4, 9),
      Point::of(0, 3),
      Point::of(1, 3),
      Point::of(2, 3),
      Point::of(3, 3),
      Point::of(5, 3),
      Point::of(6, 3),
      Point::of(7, 3),
      Point::of(8, 3)};
  Rule rule = Rule::create(&board).at(Point::of(4, 3)).getPlusShape();
  vector<Point *> actual = rule.getPossibleMove();
  listPossibleMoveCmp(expect, actual);
}

TEST(RunTest, testGetPlusShapeCase2)
{
  MockBoard board;
  vector<Point *> expect = {
      Point::of(8, 0),
      Point::of(8, 1),
      Point::of(8, 2),
      Point::of(8, 4),
      Point::of(8, 5),
      Point::of(8, 6),
      Point::of(8, 7),
      Point::of(8, 8),
      Point::of(8, 3),
      Point::of(0, 9),
      Point::of(1, 9),
      Point::of(2, 9),
      Point::of(3, 9),
      Point::of(5, 9),
      Point::of(6, 9),
      Point::of(7, 9),
      Point::of(4, 9)};
  Rule rule = Rule::create(&board).at(Point::of(8, 9)).getPlusShape();

  vector<Point *> actual = rule.getPossibleMove();
  listPossibleMoveCmp(expect, actual);
}

TEST(RunTest, testGetCrossShapeCase1)
{
  MockBoard board;
  vector<Point *> expect = {
      Point::of(1, 6),
      Point::of(0, 7),
      Point::of(3, 4),
      Point::of(4, 3),
      Point::of(5, 2),
      Point::of(6, 1),
      Point::of(7, 0),
      Point::of(1, 4),
      Point::of(0, 3),
      Point::of(3, 6),
      Point::of(4, 7),
      Point::of(5, 8),
      Point::of(6, 9),
  };
  Rule rule = Rule::create(&board).at(Point::of(2, 5)).getCrossShape();

  vector<Point *> actual = rule.getPossibleMove();
  listPossibleMoveCmp(expect, actual);
}

TEST(RunTest, testGetPlusCrossCase2)
{
  MockBoard board;
  vector<Point *> expect = {
      Point::of(7, 1),
      Point::of(6, 2),
      Point::of(5, 3),
      Point::of(4, 4),
      Point::of(3, 5),
      Point::of(2, 6),
      Point::of(1, 7),
      Point::of(0, 8)};
  Rule rule = Rule::create(&board).at(Point::of(8, 0)).getCrossShape();

  vector<Point *> actual = rule.getPossibleMove();
  listPossibleMoveCmp(expect, actual);
}


TEST(RunTest, testGetPlusElsCase1)
{
  MockBoard board;
  vector<Point *> expect = {
      Point::of(4, 7),
      Point::of(6, 7),
      Point::of(7, 6),
      Point::of(7, 4),
      Point::of(6, 3),
      Point::of(4, 3),
      Point::of(3, 4),
      Point::of(3, 6)};
  Rule rule = Rule::create(&board).at(Point::of(5, 5)).getElsShape();

  vector<Point *> actual = rule.getPossibleMove();
  listPossibleMoveCmp(expect, actual);
}

TEST(RunTest, testGetPlusElsCase2)
{
  MockBoard board;
  vector<Point *> expect = {
      Point::of(2, 8),
      Point::of(1, 7)};
  Rule rule = Rule::create(&board).at(Point::of(0, 9)).getElsShape();

  vector<Point *> actual = rule.getPossibleMove();
  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}
TEST(RunTest, testExcludeHobbling1)
{
  MockBoard board;
  vector<Point *> expect = {
      Point::of(7, 6),
      Point::of(7, 4),
      Point::of(6, 3),
      Point::of(4, 3)};
  EXPECT_CALL(board,isOccupied(5,6))
              .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(4,5))
              .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(6,5))
              .WillOnce(Return(false));
  EXPECT_CALL(board,isOccupied(5,4))
              .WillOnce(Return(false));  
  Rule rule = Rule::create(&board).at(Point::of(5, 5)).getElsShape().excludeHobbling();

  vector<Point *> actual = rule.getPossibleMove();
  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}
TEST(RunTest, testExcludeHobbling2)
{
  MockBoard board;
  vector<Point *> expect = {
      Point::of(2, 8)};
  EXPECT_CALL(board,isOccupied(0,8))
              .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(1,9))
              .WillOnce(Return(false));
  EXPECT_CALL(board,isOccupied(0,10))
              .WillOnce(Return(false));
  EXPECT_CALL(board,isOccupied(-1,9))
              .WillOnce(Return(false));  
  Rule rule = Rule::create(&board).at(Point::of(0, 9)).getElsShape().excludeHobbling();

  vector<Point *> actual = rule.getPossibleMove();
  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}
TEST(RunTest, testExcludeChessmen1)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

  EXPECT_CALL(board,isOccupied(3,4))
              .WillOnce(Return(false));
  EXPECT_CALL(board,isOccupied(3,6))
              .WillOnce(Return(false));       
  EXPECT_CALL(board,isOccupied(7,4))
              .WillOnce(Return(false));
  EXPECT_CALL(board,isOccupied(4,3))
              .WillOnce(Return(false));       

  EXPECT_CALL(board,isOccupied(4,7))
              .WillOnce(Return(true));       
  EXPECT_CALL(board,isOccupied(6,7))
              .WillOnce(Return(true));       
  EXPECT_CALL(board,isOccupied(7,6))
              .WillOnce(Return(true));       
  EXPECT_CALL(board,isOccupied(6,3))
              .WillOnce(Return(true));
  EXPECT_CALL(board,getChessman(4,7))
              .WillOnce(Return(&blackChessman));
  EXPECT_CALL(board,getChessman(6,7))
              .WillOnce(Return(&blackChessman));
  EXPECT_CALL(board,getChessman(7,6))
              .WillOnce(Return(&redChessman));
  EXPECT_CALL(board,getChessman(6,3))
              .WillOnce(Return(&redChessman));
  EXPECT_CALL(board,getChessman(5,5))
              .WillOnce(Return(&targetChessman));         

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
    
  vector<Point *> expect = {
      Point::of(4,7),
      Point::of(6,7),
      Point::of(7,4),
      Point::of(4,3),
      Point::of(3,4),
      Point::of(3,6)  
  };
  Rule rule = Rule::create(&board).at(Point::of(5, 5)).
        getElsShape().excludeChessmen();
  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testGmockBoard)
{
  MockBoard board;
  EXPECT_CALL(board,isOccupied(0,3))
              .WillOnce(Return(true));
  Rule rule = Rule::create(&board).at(Point::of(4,3)).getPlusShape().getValid();
  
}

// TEST(RunTest, testHorseChessmen)
// {
//   MockBoard board;
//   EXPECT_CALL(board,isOccupied(0,3))
//               .WillOnce(Return(true));
//   Rule rule = Rule::create(&board).at(Point::of(4,3)).getPlusShape().getValid();
  
// }