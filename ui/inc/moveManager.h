#pragma once
#include "iBoard.h"
#include "board.h"
#include "mainDialog.h"
// #include "transfer.h"
class MoveManager {
    public:
    explicit MoveManager(MainDialog* mainDialog);

    void setSourcePoint(Point* source);
    Point* getSourcePoint();
    void setDestPoint(Point* dest);
    Point* getDestPoint();
    // Set/ Unset to draw/ re-draw possible moves with different colors
    void decorateTargetedPieces(bool value);
    void movePiece(bool isNotify);
    void movePieceTransferCb(Point* from, Point* to);
    void selPieceTransferCb(Point* from);
    void calculatePossibleMoves(bool isNotify);
    Transfer *transfer;

    private:
    IBoard* board;
    MainDialog* mainDialog;
    Point* source;
    Point* dest;
    vector<Point*> possibleMoves;
    
};