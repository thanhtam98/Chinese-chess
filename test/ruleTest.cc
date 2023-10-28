#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>

#include "constant.h"
#include "point.h"
#include "rule.h"
#include "ruleShapeBuilder.h"
#include "ruleTargetBuilder.h"
#include "test/mockBoard.h"
#include "test/mockChessman.h"
#include "abstractBehaviorProvider.h"
#include "cannonBehaviorProvider.h"
#include "chariotBehaviorProvider.h"
#include "defaultBehaviorProvider.h"
#include "soldierBehaviorProvider.h"


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

TEST(RunTest, testHorseChessman1)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

/* Hobbling */
  EXPECT_CALL(board,isOccupied(Point::of(4,4)))
              .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(Point::of(5,3)))
              .WillOnce(Return(true));       
  EXPECT_CALL(board,isOccupied(Point::of(4,2)))
              .WillOnce(Return(false));
  EXPECT_CALL(board,isOccupied(Point::of(3,3)))
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

  EXPECT_CALL(board,getChessman(Point::of(3,1)))
              .WillOnce(Return(&redChessman)); 
  EXPECT_CALL(board,getChessman(Point::of(2,2)))
              .WillOnce(Return(&blackChessman));
 /* */
  EXPECT_CALL(board,getChessman(Point::of(4,3)))
              .WillRepeatedly(Return(&targetChessman));         
  EXPECT_CALL(board,getChessman(4,3))
              .WillOnce(Return(&targetChessman));  

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(HORSE));  
  vector<Point *> expect = {
      Point::of(2,4),
      Point::of(3,1),
      Point::of(5,1) 
  };
  
  Rule rule = Rule::create(&board).at(Point::of(4, 3)).getShape();
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
  EXPECT_CALL(board,isOccupied(Point::of(8,8)))
              .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(Point::of(7,9)))
              .WillOnce(Return(false));  

/* Exclude chessmen */

  EXPECT_CALL(board,isOccupied(6,8))
              .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(6,10))
              .WillRepeatedly(Return(false));  

  EXPECT_CALL(board,getChessman(Point::of(6,8)))
              .WillOnce(Return(&redChessman)); 
 /* */
  EXPECT_CALL(board,getChessman(Point::of(8,9)))
             .WillRepeatedly(Return(&targetChessman));  
  EXPECT_CALL(board,getChessman(8,9))
             .WillOnce(Return(&targetChessman));  
  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(HORSE));  
    
  vector<Point *> expect = {
  };
  Rule rule = Rule::create(&board).at(Point::of(8,9)).getShape();
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
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(CHARIOT));
    
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

  Rule rule = Rule::create(&board).at(Point::of(2, 3)).getShape();

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
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(CHARIOT));

  vector<Point *> expect = {
      Point::of(8, 1)
  };

  Rule rule = Rule::create(&board).at(Point::of(8, 0)).getShape();
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
              .WillRepeatedly(Return(&blackChessman));

  EXPECT_CALL(board,getChessman(3,3))
              .WillRepeatedly(Return(&targetChessman)); 

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
              
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(SOLDIER));

  vector<Point *> expect = {
      Point::of(3, 4)
  };

  Rule rule = Rule::create(&board).at(Point::of(3, 3)).getShape();

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

   EXPECT_CALL(board,isOccupied(5,8))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(6,7))
              .WillOnce(Return(true)); 
   EXPECT_CALL(board,isOccupied(4,7))
              .WillOnce(Return(false));             
/* Exclude chessmen */
  EXPECT_CALL(board,getChessman(5,8))
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
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(SOLDIER));    
  vector<Point *> expect = {
      Point::of(6, 7),
      Point::of(4, 7)

  };
  auto predicate = [] (Point *point, Rule &rule) {
    return false;
  };
  std::vector <direction_code> list = {NORTH};

  Rule rule = Rule::create(&board).at(Point::of(5, 7)).getShape();

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
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(CANNON));   
  vector<Point *> expect = {
      Point::of(3, 0),
      Point::of(3, 1),
      Point::of(3, 3),
      Point::of(3, 4),
      Point::of(4, 2),
      Point::of(1, 2)
  };

  Rule rule = Rule::create(&board).at(Point::of(3, 2)).getShape();

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
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(CANNON));  
    
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

  Rule rule = Rule::create(&board).at(Point::of(8, 4)).getShape();
  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testAdvisorChessman1)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

  EXPECT_CALL(board,isOccupied(4,1))
              .WillOnce(Return(true));
  // EXPECT_CALL(board,isOccupied(2,1))
  //             .WillOnce(Return(false)); 

  EXPECT_CALL(board,getChessman(4,1))
              .WillOnce(Return(&blackChessman));

  EXPECT_CALL(board,getChessman(3,0))
              .WillRepeatedly(Return(&targetChessman)); 

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(ADVISOR));  
    
  vector<Point *> expect = {
      Point::of(4, 1)
  };

  Rule rule = Rule::create(&board).at(Point::of(3, 0)).getShape();
  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testAdvisorChessman2)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

  EXPECT_CALL(board,isOccupied(5,7))
              .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(5,9))
              .WillOnce(Return(true));  
  EXPECT_CALL(board,isOccupied(3,7))
              .WillOnce(Return(false));
  EXPECT_CALL(board,isOccupied(3,9))
              .WillOnce(Return(false));

  EXPECT_CALL(board,getChessman(5,7))
              .WillOnce(Return(&blackChessman));
  EXPECT_CALL(board,getChessman(5,9))
              .WillOnce(Return(&redChessman));
  EXPECT_CALL(board,getChessman(4,8))
              .WillRepeatedly(Return(&targetChessman)); 

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(ADVISOR));  
    
  vector<Point *> expect = {
      Point::of(5, 7),
      Point::of(3, 9),
      Point::of(3, 7)
  };

  Rule rule = Rule::create(&board).at(Point::of(4, 8)).getShape();
  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testElephantChessman1)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

  EXPECT_CALL(board,isOccupied(Point::of(2,0)))
              .WillRepeatedly(Return(true));
  EXPECT_CALL(board,isOccupied(Point::of(6,0)))
              .WillRepeatedly(Return(true));  
  EXPECT_CALL(board,isOccupied(Point::of(2,4)))
              .WillRepeatedly(Return(false));
  EXPECT_CALL(board,isOccupied(Point::of(6,4)))
              .WillRepeatedly(Return(false));
  EXPECT_CALL(board,isOccupied(Point::of(3,1)))
              .WillRepeatedly(Return(false));
  EXPECT_CALL(board,isOccupied(Point::of(3,3)))
              .WillRepeatedly(Return(false));
  EXPECT_CALL(board,isOccupied(Point::of(5,1)))
              .WillRepeatedly(Return(false));
  EXPECT_CALL(board,isOccupied(Point::of(5,3)))
              .WillRepeatedly(Return(false));  

  EXPECT_CALL(board,getChessman(Point::of(2,0)))
              .WillOnce(Return(&redChessman));
  EXPECT_CALL(board,getChessman(Point::of(6,0)))
              .WillOnce(Return(&blackChessman));
  EXPECT_CALL(board,getChessman(Point::of(4,2)))
              .WillRepeatedly(Return(&targetChessman)); 
  EXPECT_CALL(board,getChessman(4,2))
              .WillRepeatedly(Return(&targetChessman)); 

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(ELEPHANT));  
    
  vector<Point *> expect = {
      Point::of(6, 0),
      Point::of(6, 4),
      Point::of(2, 4)
  };

  Rule rule = Rule::create(&board).at(Point::of(4, 2)).getShape();
  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testElephantChessman2)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

  EXPECT_CALL(board,isOccupied(Point::of(4,2)))
              .WillRepeatedly(Return(true));
  // EXPECT_CALL(board,isOccupied(4,2))
  //             .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(Point::of(1,3)))
              .WillOnce(Return(true));  

  EXPECT_CALL(board,isOccupied(Point::of(3,3)))
              .WillOnce(Return(false));  
  EXPECT_CALL(board,isOccupied(Point::of(1,5)))
              .WillOnce(Return(false));  
  EXPECT_CALL(board,isOccupied(Point::of(0,6)))
              .WillOnce(Return(false));  
  EXPECT_CALL(board,isOccupied(Point::of(3,5)))
              .WillOnce(Return(false));  
  EXPECT_CALL(board,isOccupied(Point::of(4,6)))
              .WillOnce(Return(false));  
            
  EXPECT_CALL(board,getChessman(Point::of(4,2)))
              .WillOnce(Return(&redChessman));
  // EXPECT_CALL(board,getChessman(Point::of(1,3)))
  //             .WillOnce(Return(&blackChessman));
  EXPECT_CALL(board,getChessman(Point::of(2,4)))
              .WillRepeatedly(Return(&targetChessman)); 
  EXPECT_CALL(board,getChessman(2,4))
              .WillRepeatedly(Return(&targetChessman)); 

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(ELEPHANT));  
    
  vector<Point *> expect = {};

  Rule rule = Rule::create(&board).at(Point::of(2, 4)).getShape();
  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}

TEST(RunTest, testGeneralChessman1)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

  EXPECT_CALL(board,isOccupied(Point::of(3,0)))
              .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(Point::of(5,0)))
              .WillOnce(Return(true));  

  EXPECT_CALL(board,isOccupied(Point::of(4,1)))
              .WillOnce(Return(false));  

            
  EXPECT_CALL(board,getChessman(Point::of(5,0)))
              .WillOnce(Return(&blackChessman));
  EXPECT_CALL(board,getChessman(Point::of(3,0)))
              .WillOnce(Return(&redChessman)); 
  EXPECT_CALL(board,getChessman(4,0))
              .WillRepeatedly(Return(&targetChessman));

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(GENERAL));  
  vector<Point *> expect = {
    Point::of(5,0),
    Point::of(4,1)
  };

  Rule rule = Rule::create(&board).at(Point::of(4, 0)).getShape();
  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}


TEST(RunTest, testGeneralChessman2)
{
  MockBoard board;
  MockChessman targetChessman; // red
  MockChessman blackChessman;
  MockChessman redChessman;

  EXPECT_CALL(board,isOccupied(Point::of(4,7)))
              .WillOnce(Return(true));
  EXPECT_CALL(board,isOccupied(Point::of(3,8)))
              .WillOnce(Return(false));
            
  EXPECT_CALL(board,getChessman(Point::of(4,7)))
              .WillOnce(Return(&redChessman));
  EXPECT_CALL(board,getChessman(3,7))
              .WillRepeatedly(Return(&targetChessman));

  EXPECT_CALL(targetChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(blackChessman, getTeam())
              .WillRepeatedly(Return(BLACK));
  EXPECT_CALL(redChessman, getTeam())
              .WillRepeatedly(Return(RED));
  EXPECT_CALL(targetChessman, getCode())
              .WillOnce(Return(GENERAL));  
  vector<Point *> expect = {
    Point::of(4,7),
    Point::of(3,8)
  };

  Rule rule = Rule::create(&board).at(Point::of(3,7)).getShape();
  vector<Point *> actual = rule.getPossibleMove();

  listPossibleMoveCmp(expect, actual);
  // MOCK_METHOD
}