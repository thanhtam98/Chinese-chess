#include "mainDialog.h"
#include "board.h"
#include "iChessman.h"
#include "constant.h"
#include "ILabel.h"
#include "pieceLabel.h"
#include "spaceLabel.h"
#include "ITurn.h"
#include "offlineTurn.h"
#include "debugTurn.h"
#include "teamSignalLabels.h"
#include <string>
#include "moveManager.h"

using namespace std;

MainDialog::MainDialog(FWidget* parent) : FDialog{parent} {
    board = Board::getInstance();
    LOG_F("Initialize the Board Dialog");

    // ITurn::setup(new DebugTurn(), new DebugTurn());

    // for (int x = 0; x < BOARD_WIDTH; x++) {
    //     for (int y = 0; y < BOARD_LENGTH; y++) {
    //         IChessman* chessman = board->getChessman(x, BOARD_LENGTH - y -1);
    //         if (chessman) {
    //             pieces[x][y] = new PieceLabel{this, Point::of(x, y)};
    //             addCallback(pieces[x][y], "clicked");
    //         } else {
    //             pieces[x][y] = new SpaceLabel{this, Point::of(x, y)};
    //         }
    //         addCallback(pieces[x][y], "move");
    //     }
    // }
    // teamSignalLabels = new TeamSignalLabels{this};
    // moveManager = new MoveManager{this};
    // endGameLabel.show(GAME_OVER, FColor::Cyan, FColor::BlueViolet);
    introTimerId = addTimer(200);
    pressKeyTimerId = addTimer(500);
    barsTimerId = addTimer(1500);
    introLabel = new IntroLabel{this};
    // introLabel.showAll();
}

void MainDialog::initLayout() {
    FDialog::initLayout();
}

void MainDialog::dispatchChessmanMove(Point* source, Point* destination) {
    moveManager->movePiece();
    ITurn::end();
    teamSignalLabels->changeTeamColor();
}

void MainDialog::clickedCallback() {
    moveManager->calculatePossibleMoves();
    // debugLabel.log(pieces[moveManager->getSourcePoint()->getX()][moveManager->getSourcePoint()->getY()]->getText().toString());
    redraw();
}

void MainDialog::moveCallback() {
    moveManager->decorateTargetedPieces(false);
    // Swap 2 pieces in case of normal move
    moveManager->movePiece();
    ITurn::end();
    teamSignalLabels->changeTeamColor();
}

void MainDialog::addCallback(ILabel* label, string event) {
    label->addCallback(
        event,
        this,
        event.compare("move") == 0 ? &MainDialog::moveCallback : &MainDialog::clickedCallback
    );
}

void MainDialog::onTimer(FTimerEvent* event) {
    if (event->getTimerId() == introTimerId) {
        introLabel->setColor();
    }
    if (event->getTimerId() == pressKeyTimerId) {
        introLabel->togglePressKey();
    }
    if (event->getTimerId() == barsTimerId) {
        introLabel->toggleBars();
    }
    redraw();
}