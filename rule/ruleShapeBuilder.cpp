#include "rule/ruleShapeBuilder.h"
#include "rule/ruleLimitBuilder.h"
#include "utils/constant.h"

void RuleShapeBuilder::getPlusShapeHelper(Point *point,std::function<bool(Point *point)> predicate)
{
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    IChessman *chessman;
    IBoard *board = rule.board;
    Point* target = rule.target;
    int x = target->getX();
    int y = target->getY();
    IChessman *targetChessman = board->getChessman(x,y);

    if (predicate(point)){
            possibleMoves->push_back(point);
        }else{
            chessman = board->getChessman(point->getX(),point->getY());
            if (chessman->getTeam() != targetChessman->getTeam()){
                possibleMoves->push_back(point);
            }
            return;
    }
}
RuleLimitBuilder RuleShapeBuilder::getPlusShape(std::function<bool(Point *point)> predicate) {
    Point* target = rule.target;
    vector<Point*> *possibleMoves = &(rule.possibleMoves);
    int x = target->getX();
    int y = target->getY();
    IBoard *board = rule.board;
    IChessman *targetChessman = board->getChessman(x,y);
    IChessman *chessman;

    /* Left ->  */
    for (int i = x+1; i < BOARD_WIDTH; i++){
        getPlusShapeHelper(Point::of(i,y), predicate);
    }
    /* Right <-  */
    for (int i = x-1; i >= 0; i--){
        getPlusShapeHelper(Point::of(i,y), predicate);
    }
    /* Up  /\ */
    for (int i = y+1; i < BOARD_LENGTH; i++){
        getPlusShapeHelper(Point::of(x,i), predicate);
    }
    /* Down \/ */
    for (int i = y-1; i >= 0; i--){
        getPlusShapeHelper(Point::of(x,i), predicate);
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