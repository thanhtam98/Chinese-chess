#pragma once
#include "iBoard.h"
#include "board.h"
#include "boardDialog.h"

class MoveManager {
    public:
    explicit MoveManager(BoardDialog* boardDialog);

    void setSourcePoint(Point* source);
    Point* getSourcePoint();
    void setDestPoint(Point* dest);
    Point* getDestPoint();
    // Set/ Unset to draw/ re-draw possible moves with different colors
    void decorateTargetedPieces(bool value);
    void movePiece();
    void calculatePossibleMoves();

    private:
    IBoard* board;
    BoardDialog* mainDialog;
    Point* source;
    Point* dest;
    vector<Point*> possibleMoves;
};