#pragma once
#include "iBoard.h"
#include "board.h"
#include "mainDialog.h"
#include "umpire.h"

class MoveManager {
    public:
    explicit MoveManager(MainDialog* mainDialog);

    void setSourcePoint(Point* source);
    Point* getSourcePoint();
    void setDestPoint(Point* dest);
    Point* getDestPoint();
    // Set/ Unset to draw/ re-draw possible moves with different colors
    void decorateTargetedPieces(bool value);
    void decoratePotentialPieces(bool value);
    void movePiece();
    void calculatePossibleMoves();
    void calculatePossiblePotentials();
    private:
    IBoard* board;
    Umpire* umpire;
    MainDialog* mainDialog;
    Point* source;
    Point* dest;
    vector<Point*> possibleMoves;
    vector<Point*> possiblePotentials;
};