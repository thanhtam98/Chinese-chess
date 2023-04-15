#include "ui/BoardDialog.h"
#include "logic/board.h"
#include "logic/iChessman.h"
#include "utils/constant.h"
#include "ui/label/ILabel.h"
#include "ui/label/pieceLabel.h"
#include "ui/label/spaceLabel.h"
#include <string>

using namespace std;

BoardDialog::BoardDialog(FWidget* parent) : FDialog{parent} {
    board = Board::getInstance();
    cout << "Init board" << endl;

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            IChessman* chessman = board->getChessman(x, BOARD_LENGTH - y -1);
            if (chessman) {
                pieces[x][y] = new PieceLabel{this, Point::of(x, y)};
            } else {
                pieces[x][y] = new SpaceLabel{this, Point::of(x, y)};
            }
            pieces[x][y]->addCallback(
                "clicked",
                this,
                &BoardDialog::clickedCallback
            );
        }
    }
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