#include "boardDialog.h"
#include "board.h"
#include "iChessman.h"
#include "utils.h"
#include "ILabel.h"
#include "pieceLabel.h"
#include "spaceLabel.h"
#include "ITurn.h"
#include "offlineTurn.h"
#include "debugTurn.h"
#include "teamSignalLabels.h"
#include <string>

using namespace std;

BoardDialog::BoardDialog(FWidget* parent) : FDialog{parent} {
    board = Board::getInstance();
    LOG_F("Initialize the Board Dialog");

    ITurn::setupTurns(new DebugTurn(), new DebugTurn());
    // ITurn::setupTurns(new OfflineTurn(RED), new OfflineTurn(BLACK));

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            IChessman* chessman = board->getChessman(x, BOARD_LENGTH - y -1);
            if (chessman) {
                pieces[x][y] = new PieceLabel{this, Point::of(x, y)};
                pieces[x][y]->addCallback(
                    "clicked",
                    this,
                    &BoardDialog::clickedCallback
                );
            } else {
                pieces[x][y] = new SpaceLabel{this, Point::of(x, y)};
            }
            pieces[x][y]->addCallback(
                "move",
                this,
                &BoardDialog::moveCallback
            );
        }
    }
    teamSignalLabels = new TeamSignalLabels{this};
}

void BoardDialog::initLayout() {
    FDialog::initLayout();
}

void BoardDialog::dispatchChessmanMove(Point* source, Point* destination) {
    swapPieces();
    ITurn::endTurn();
    teamSignalLabels->changeTeamColor();
}

void BoardDialog::setSourcePoint(Point* clicked) {
    sourcePoint = clicked;
}
Point* BoardDialog::getSourcePoint() {
    return sourcePoint;
}

void BoardDialog::setDestPoint(Point* to) {
    destPoint = to;
}
Point* BoardDialog::getDestPoint() {
    return destPoint;
}

void BoardDialog::clickedCallback() {
    setValueForTargetedPieces(false);
    possibleMoves = board->getPossibleMoves(sourcePoint);
    setValueForTargetedPieces(true);

    debugLabel.log(pieces[sourcePoint->getX()][sourcePoint->getY()]->getText().toString());
    redraw();
}

void BoardDialog::setValueForTargetedPieces(bool value) {
    for (Point* point : possibleMoves) {
        if (value) {
            pieces[point->getX()][point->getY()]->setTarget();
        } else {
            pieces[point->getX()][point->getY()]->unsetTarget();
        }
    }
}

void BoardDialog::moveCallback() {
    setValueForTargetedPieces(false);
    // Swap 2 pieces in case of normal move
    swapPieces();
    ITurn::endTurn();
    teamSignalLabels->changeTeamColor();
}

void BoardDialog::swapPieces() {
    ILabel* toPiece = pieces[destPoint->getX()][destPoint->getY()];
    ILabel* fromPiece = pieces[sourcePoint->getX()][sourcePoint->getY()];
    if (dynamic_cast<SpaceLabel*>(toPiece) != nullptr) {
        // If toPiece is a space label, we swap to labels
        fromPiece->changePosition(destPoint);
        toPiece->changePosition(sourcePoint);

        // Swap the pieces in pieces array of the board dialog
        pieces[sourcePoint->getX()][sourcePoint->getY()] = toPiece;
        pieces[destPoint->getX()][destPoint->getY()] = fromPiece;

    } else {
        // If toPiece is a piece label, we delete the destined piece label
        // (considered as eliminated), move the source piece label and
        // create a space label where the source piece label was located.
        fromPiece->changePosition(destPoint);
        toPiece->changePosition(sourcePoint);
        toPiece->hide();

        delete toPiece;
        pieces[destPoint->getX()][destPoint->getY()] = fromPiece;
        ILabel* newLabel = new SpaceLabel{this, sourcePoint};
        pieces[sourcePoint->getX()][sourcePoint->getY()] = newLabel;
        newLabel->show();
        // newLabel->addCallback(
        //     "clicked",
        //     this,
        //     &BoardDialog::clickedCallback
        // );
        newLabel->addCallback(
            "move",
            this,
            &BoardDialog::moveCallback
        );
    }

    // Inform the board about the changes.
    board->move(sourcePoint, destPoint);
}