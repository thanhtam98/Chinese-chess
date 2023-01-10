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
#include "rule/behaviorProvider/abstractBehaviorProvider.h"
#include "rule/behaviorProvider/cannonBehaviorProvider.h"
#include "rule/behaviorProvider/chariotBehaviorProvider.h"
#include "rule/behaviorProvider/defaultBehaviorProvider.h"
#include "rule/behaviorProvider/soldierBehaviorProvider.h"


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
  Rule rule = Rule::create(&board).at(Point::of(4, 3)).getPlusShape(new DefaultBehaviorProvider());
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
  Rule rule = Rule::create(&board).at(Point::of(8, 9)).getPlusShape(new DefaultBehaviorProvider());

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

TEST(RunTest, testHorseChessman1)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

/* Hobbling */
  EXPECT_CALL(board,isOccupied(4,4))
              .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(5,3))
              .WillOnce(Return(true));       
  EXPECT_CALL(board,isOccupied(4,2))
              .WillOnce(Return(false));
  EXPECT_CALL(board,isOccupied(3,3))
              .WillOnce(Return(false));       
/* Exclude chessmen */
  EXPECT_CALL(board,isOccupied(2,4))
              .WillOnce(Return(false));       
  EXPECT_CALL(board,isOccupied(5,1))
              .WillOnce(Return(false));              
  EXPECT_CALL(board,isOccupied(3,1))
              .WillOnce(Return(true)); 
  EXPECT_CALL(board,isOccupied(2,2))
              .WillOnce(Return(true));

  EXPECT_CALL(board,getChessman(3,1))
              .WillOnce(Return(&redChessman)); 
  EXPECT_CALL(board,getChessman(2,2))
              .WillOnce(Return(&blackChessman));
 /* */
  EXPECT_CALL(board,getChessman(4,3))
              .WillOnce(Return(&blackChessman));         

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
    
  vector<Point *> expect = {
      Point::of(2,4),
      Point::of(3,1),
      Point::of(5,1) 
  };
  Rule rule = Rule::create(&board).at(Point::of(4, 3)).
        getElsShape().excludeHobbling().excludeChessmen();
  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testHorseChessman2)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

/* Hobbling */
  EXPECT_CALL(board,isOccupied(8,8))
              .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(9,9))
              .WillOnce(Return(false));  
  EXPECT_CALL(board,isOccupied(7,9))
              .WillOnce(Return(false));  
  EXPECT_CALL(board,isOccupied(8,10))
              .WillOnce(Return(false));  
/* Exclude chessmen */
  EXPECT_CALL(board,isOccupied(6,8))
              .WillOnce(Return(true));

  EXPECT_CALL(board,getChessman(6,8))
              .WillOnce(Return(&redChessman)); 
 /* */
  EXPECT_CALL(board,getChessman(8,9))
              .WillOnce(Return(&redChessman));         

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
    
  vector<Point *> expect = {
  };
  Rule rule = Rule::create(&board).at(Point::of(8,9)).
        getElsShape().excludeHobbling().excludeChessmen();
  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}


TEST(RunTest, testChariotChessman1)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

  EXPECT_CALL(board,isOccupied(2,0))
              .WillOnce(Return(false));
  EXPECT_CALL(board,isOccupied(2,1))
              .WillOnce(Return(false));  
  EXPECT_CALL(board,isOccupied(2,2))
              .WillOnce(Return(false));  
  EXPECT_CALL(board,isOccupied(2,4))
              .WillOnce(Return(false));  
   EXPECT_CALL(board,isOccupied(2,5))
              .WillOnce(Return(false));  
   EXPECT_CALL(board,isOccupied(2,6))
              .WillOnce(Return(false));  
   EXPECT_CALL(board,isOccupied(0,3))
              .WillOnce(Return(false));  
   EXPECT_CALL(board,isOccupied(1,3))
              .WillOnce(Return(false));  
   EXPECT_CALL(board,isOccupied(3,3))
              .WillOnce(Return(false));  
   EXPECT_CALL(board,isOccupied(4,3))
              .WillOnce(Return(false));  

   EXPECT_CALL(board,isOccupied(2,7))
              .Times(2).WillOnce(Return(true)).WillOnce(Return(true));  
   EXPECT_CALL(board,isOccupied(5,3))
              .Times(2).WillOnce(Return(true)).WillOnce(Return(true));            
/* Exclude chessmen */
  EXPECT_CALL(board,getChessman(2,7))
              .WillOnce(Return(&blackChessman));
  EXPECT_CALL(board,getChessman(5,3))
              .WillOnce(Return(&redChessman));

  EXPECT_CALL(board,getChessman(2,3))
              .WillRepeatedly(Return(&targetChessman)); 

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
    
  vector<Point *> expect = {
      Point::of(2, 0),
      Point::of(2, 1),
      Point::of(2, 2),
      Point::of(2, 4),
      Point::of(2, 5),
      Point::of(2, 6),
      Point::of(0, 3),
      Point::of(1, 3),
      Point::of(3, 3),
      Point::of(4, 3),
      Point::of(2, 7)
  };

  Rule rule = Rule::create(&board).at(Point::of(2, 3)).getPlusShape(new ChariotBehaviorProvider());

  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testChariotChessman2)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

   EXPECT_CALL(board,isOccupied(7,0))
              .Times(2).WillOnce(Return(true)).WillOnce(Return(true));            
   EXPECT_CALL(board,isOccupied(8,1))
              .Times(2).WillOnce(Return(true)).WillOnce(Return(true));            
/* Exclude chessmen */
  EXPECT_CALL(board,getChessman(7,0))
              .WillOnce(Return(&redChessman));
  EXPECT_CALL(board,getChessman(8,1))
              .WillOnce(Return(&blackChessman));

  EXPECT_CALL(board,getChessman(8,0))
              .WillRepeatedly(Return(&targetChessman)); 

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
    
  vector<Point *> expect = {
      Point::of(8, 1)
  };

  Rule rule = Rule::create(&board).at(Point::of(8, 0)).getPlusShape(new ChariotBehaviorProvider());

  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testSoldierChessman1)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

   EXPECT_CALL(board,isOccupied(3,4))
              .WillOnce(Return(true));             
/* Exclude chessmen */
  EXPECT_CALL(board,getChessman(3,4))
              .WillOnce(Return(&blackChessman));

  EXPECT_CALL(board,getChessman(3,3))
              .WillRepeatedly(Return(&targetChessman)); 

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
              
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
    
  vector<Point *> expect = {
      Point::of(3, 4)
  };

  std::vector <direction_code> list = {SOUTH,WEST,EAST};

  Rule rule = Rule::create(&board).at(Point::of(3, 3)).getPlusShape(new SoldierBehaviorProvider(),list);
  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testSoldierChessman2)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

   EXPECT_CALL(board,isOccupied(5,6))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(6,7))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(4,7))
              .WillOnce(Return(false));             
/* Exclude chessmen */
  EXPECT_CALL(board,getChessman(5,6))
              .WillOnce(Return(&redChessman)); 
  EXPECT_CALL(board,getChessman(6,7))
              .WillOnce(Return(&blackChessman));
  EXPECT_CALL(board,getChessman(5,7))
              .WillRepeatedly(Return(&targetChessman)); 

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
    
  vector<Point *> expect = {
      Point::of(6, 7),
      Point::of(4, 7)

  };
  auto predicate = [] (Point *point, Rule &rule) {
    return false;
  };
  std::vector <direction_code> list = {NORTH};

  Rule rule = Rule::create(&board).at(Point::of(5, 7))
        .getPlusShape(new SoldierBehaviorProvider(),list);

  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testCannonChessman1)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

   EXPECT_CALL(board,isOccupied(3,5))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(3,6))
              .WillOnce(Return(true));
   EXPECT_CALL(board,isOccupied(1,2))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(2,2))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(5,2))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(6,2))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(3,0))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(3,1))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(3,3))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(3,4))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(4,2))
              .WillOnce(Return(false)); 

/* Exclude chessmen */
  EXPECT_CALL(board,getChessman(3,6))
              .WillOnce(Return(&redChessman));
  EXPECT_CALL(board,getChessman(6,2))
              .WillOnce(Return(&redChessman)); 
  EXPECT_CALL(board,getChessman(1,2))
              .WillOnce(Return(&blackChessman));
  EXPECT_CALL(board,getChessman(3,2))
              .WillRepeatedly(Return(&targetChessman)); 

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
    
  vector<Point *> expect = {
      Point::of(3, 0),
      Point::of(3, 1),
      Point::of(3, 3),
      Point::of(3, 4),
      Point::of(4, 2),
      Point::of(1, 2)
  };

  Rule rule = Rule::create(&board).at(Point::of(3, 2)).getPlusShape(new CannonBehaviorProvider());

  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testCannonChessman2)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

   EXPECT_CALL(board,isOccupied(8,0))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(8,7))
              .WillOnce(Return(true));
   EXPECT_CALL(board,isOccupied(8,9))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(0,4))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(8,1))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(8,2))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(8,3))
              .WillOnce(Return(false));
   EXPECT_CALL(board,isOccupied(8,6))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(8,8))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(8,5))
              .WillOnce(Return(false));
   EXPECT_CALL(board,isOccupied(1,4))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(2,4))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(3,4))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(4,4))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(5,4))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(6,4))
              .WillOnce(Return(false)); 
   EXPECT_CALL(board,isOccupied(7,4))
              .WillOnce(Return(false)); 

/* Exclude chessmen */
  EXPECT_CALL(board,getChessman(8,9))
              .WillOnce(Return(&blackChessman));

  EXPECT_CALL(board,getChessman(8,4))
              .WillRepeatedly(Return(&targetChessman)); 

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
    
  vector<Point *> expect = {
      Point::of(8, 1),
      Point::of(8, 2),
      Point::of(8, 3),
      Point::of(8, 5),
      Point::of(8, 6),
      Point::of(8, 9),
      Point::of(1, 4),
      Point::of(2, 4),
      Point::of(3, 4),
      Point::of(4, 4),
      Point::of(5, 4),
      Point::of(6, 4),
      Point::of(7, 4)
  };

  Rule rule = Rule::create(&board).at(Point::of(8, 4)).getPlusShape(new CannonBehaviorProvider());

  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}