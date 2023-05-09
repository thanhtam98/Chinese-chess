#include "ui/boardDialog.h"
#include "logic/board.h"
#include "logic/iChessman.h"
#include "utils/constant.h"
#include "ui/label/ILabel.h"
#include "ui/label/pieceLabel.h"
#include "ui/label/spaceLabel.h"
#include "ui/turn/ITurn.h"
#include "ui/turn/offlineTurn.h"
#include "ui/turn/debugTurn.h"
#include "ui/label/teamSignalLabels.h"
#include <string>

using namespace std;

BoardDialog::BoardDialog(FWidget* parent) : FDialog{parent} {
    board = Board::getInstance();
    cout << "Init board" << endl;

    //ITurn::setupTurns(new DebugTurn(), new DebugTurn());
    ITurn::setupTurns(new OfflineTurn(RED), new OfflineTurn(BLACK));

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

void BoardDialog::setClickedPoint(Point* clicked) {
    clickedPoint = clicked;
}
Point* BoardDialog::getClickedPoint() {
    return clickedPoint;
}

void BoardDialog::setToPoint(Point* to) {
    toPoint = to;
}
Point* BoardDialog::getToPoint() {
    return toPoint;
}

void BoardDialog::clickedCallback() {
    setValueForTargetedPieces(false);
    possibleMoves = board->getPossibleMoves(clickedPoint);
    setValueForTargetedPieces(true);

    debugLabel.log(pieces[clickedPoint->getX()][clickedPoint->getY()]->getText().toString());
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
    ILabel* toPiece = pieces[toPoint->getX()][toPoint->getY()];
    ILabel* fromPiece = pieces[clickedPoint->getX()][clickedPoint->getY()];
    if (dynamic_cast<SpaceLabel*>(toPiece) != nullptr) {
        // If toPiece is a space label, we swap to labels
        fromPiece->changePosition(toPoint);
        toPiece->changePosition(clickedPoint);

        // Swap the pieces in pieces array of the board dialog
        pieces[clickedPoint->getX()][clickedPoint->getY()] = toPiece;
        pieces[toPoint->getX()][toPoint->getY()] = fromPiece;

    } else {
        // If toPiece is a piece label, we delete the destined piece label
        // (considered as eliminated), move the source piece label and
        // create a space label where the source piece label was located.
        fromPiece->changePosition(toPoint);
        toPiece->changePosition(clickedPoint);
        toPiece->hide();

        delete toPiece;
        pieces[toPoint->getX()][toPoint->getY()] = fromPiece;
        ILabel* newLabel = new SpaceLabel{this, clickedPoint};
        pieces[clickedPoint->getX()][clickedPoint->getY()] = newLabel;
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
    board->move(clickedPoint, toPoint);
}