#pragma once
#include "iBoard.h"
#include "board.h"
#include "boardDialog.h"
#include "umpire.h"
#include "transfer.h"

class MoveManager {
    public:
    explicit MoveManager(BoardDialog* boardDialog);

    void setSourcePoint(Point* source);
    Point* getSourcePoint();
    void setDestPoint(Point* dest);
    Point* getDestPoint();
    // Set/ Unset to draw/ re-draw possible moves with different colors
    void decorateTargetedPieces(bool value);
    void decoratePotentialPieces(bool value);
    bool movePiece(bool isNotify);
    void calculatePossiblePotentials();
    bool preCalculatePossiblePotentials();
    void movePieceTransferCb(Point* from, Point* to);
    void selPieceTransferCb(Point* from);
    void calculatePossibleMoves(bool isNotify);
    void setConnectionInstance(ConnectionBase *con);

    Transfer *transfer;

    private:
    IBoard* board;
    Umpire* umpire;
    BoardDialog* mainDialog;
    Point* source;
    Point* dest;
    vector<Point*> possibleMoves;
    vector<Point*> possiblePotentials;
};