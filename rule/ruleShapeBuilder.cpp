#include "rule/ruleShapeBuilder.h"
#include "rule/ruleLimitBuilder.h"
#include "utils/constant.h"
#include "utils/utils.h"

/* ########### HANDLE IF TRUE ########### */
std::function<void(Point *point, Rule &rule)> RuleShapeBuilder::defaultHandleTrue = 
        [] (Point *point, Rule &rule) {
            vector<Point*> *possibleMoves = &(rule.possibleMoves);
            possibleMoves->push_back(point);
        };
        
/* ########### END OF HANDLE IF TRUE ########### */

/* ########### HANDLE IF FALSE ########### */
std::function<void(Point *point, Rule &rule)> RuleShapeBuilder::defaultHandleFalse = 
        [] (Point *point, Rule &rule) {
                vector<Point*> *possibleMoves = &(rule.possibleMoves);
                IChessman *chessman;
                IBoard *board = rule.board;
                Point* target = rule.target;
                int x = target->getX();
                int y = target->getY();

                if (!board->isOccupied(point->getX(),point->getY())){
                    possibleMoves->push_back(point);
                    return;
                }

                IChessman *targetChessman = board->getChessman(x,y);
                chessman = board->getChessman(point->getX(),point->getY());

                if (chessman && chessman->getTeam() != targetChessman->getTeam()){
                    possibleMoves->push_back(point);
                }
        };
std::function<void(Point *point, Rule &rule)> RuleShapeBuilder::soldierHandleFalse = 
        [] (Point *point, Rule &rule) {
                vector<Point*> *possibleMoves = &(rule.possibleMoves);
                IChessman *chessman;
                IBoard *board = rule.board;
                Point *target = rule.target;
                int x = target->getX();
                int y = target->getY();
                IChessman *targetChessman = board->getChessman(x,y);

                chessman = board->getChessman(point->getX(),point->getY());

                if (!board->isOccupied(point->getX(),point->getY())
                    && chessman && chessman->getTeam() == targetChessman->getTeam())
                    return;
                if (chessman && chessman->getTeam() != targetChessman->getTeam()){
                    possibleMoves->push_back(point);
                }
        };
/* ########### END OF HANDLE IF FALSE ########### */

bool RuleShapeBuilder::isContinuedAndAddPossibleMoves(Point *point,std::function<bool(Point *point, Rule &rule)> predicate,
        std::function<void(Point *point, Rule &rule)> handleTrue, 
        std::function<void(Point *point, Rule &rule)> handleFalse)
{
    if (predicate(point, rule))
    {
        handleTrue(point, rule);
        return true;
    }
    else
    {
        handleFalse(point, rule);
        return false;
    }
}
RuleLimitBuilder RuleShapeBuilder::getPlusShape(std::function<bool(Point *point, Rule &rule)> predicate,
        std::vector<direction_code> denyDirList,
        std::function<void(Point *point, Rule &rule)> handleTrue , 
        std::function<void(Point *point, Rule &rule)> handleFalse ){
    Point* target = rule.target;
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    int x = target->getX();
    int y = target->getY();
    IBoard *board = rule.board;
    IChessman *targetChessman = board->getChessman(x,y);
    IChessman *chessman;

    /* Left ->  */
    if (!Utils::isDirContainsInList(denyDirList, LEFT))
        for (int i = x+1; i < BOARD_WIDTH; i++){
            if (isContinuedAndAddPossibleMoves(Point::of(i,y), predicate,handleTrue,handleFalse) == false)
                break;
    }
    /* Right <-  */
    if (!Utils::isDirContainsInList(denyDirList, RIGHT))
    {
        for (int i = x-1; i >= 0; i--){
            if (isContinuedAndAddPossibleMoves(Point::of(i,y), predicate,handleTrue,handleFalse) == false)
                break;
        }
    }
    /* Up  /\ */
    if (!Utils::isDirContainsInList(denyDirList, UP))
    {
        for (int i = y+1; i < BOARD_LENGTH; i++){
            if (isContinuedAndAddPossibleMoves(Point::of(x,i), predicate,handleTrue,handleFalse) == false)
                break;
        }
    }
    /* Down \/ */
    if (!Utils::isDirContainsInList(denyDirList, DOWN))
    {
        for (int i = y-1; i >= 0; i--){
            if (isContinuedAndAddPossibleMoves(Point::of(x,i), predicate,handleTrue,handleFalse) == false)
                break;
        }
    }
  
    return RuleLimitBuilder{rule};
}

RuleLimitBuilder RuleShapeBuilder::getCrossShape() {
    Point* target = rule.target;
    int x = target->getX();
    int y = target->getY();
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    for (int i = x+1, j = y+1; i < BOARD_WIDTH && j < BOARD_LENGTH; i++, j++) {
        possibleMoves->push_back(Point::of(i, j));   
    }
    for (int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) {
        possibleMoves->push_back(Point::of(i, j));
    }
    for (int i = x+1, j = y-1; i < BOARD_WIDTH && j >= 0; i++, j--) {
        possibleMoves->push_back(Point::of(i, j));
    }
    for (int i = x-1, j = y+1; i >= 0 && j < BOARD_LENGTH; i--, j++) {
        possibleMoves->push_back(Point::of(i, j));
    }

    return RuleLimitBuilder{rule};
}

RuleLimitBuilder RuleShapeBuilder::getElsShape() {
    Point* target = rule.target;
    int x = target->getX();
    int y = target->getY();
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    
    if (Point::isWithinBoundary(x+1, y+2)) possibleMoves->push_back(Point::of(x+1, y+2));
    if (Point::isWithinBoundary(x+1, y-2)) possibleMoves->push_back(Point::of(x+1, y-2));
    if (Point::isWithinBoundary(x-1, y+2)) possibleMoves->push_back(Point::of(x-1, y+2));
    if (Point::isWithinBoundary(x-1, y-2)) possibleMoves->push_back(Point::of(x-1, y-2));
    if (Point::isWithinBoundary(x+2, y+1)) possibleMoves->push_back(Point::of(x+2, y+1));
    if (Point::isWithinBoundary(x+2, y-1)) possibleMoves->push_back(Point::of(x+2, y-1));
    if (Point::isWithinBoundary(x-2, y+1)) possibleMoves->push_back(Point::of(x-2, y+1));
    if (Point::isWithinBoundary(x-2, y-1)) possibleMoves->push_back(Point::of(x-2, y-1));
    
    return RuleLimitBuilder{rule};
}