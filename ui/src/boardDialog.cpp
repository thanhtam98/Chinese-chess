#include "boardDialog.h"
#include "board.h"
#include "ITurn.h"
#include "debugTurn.h"
#include "pieceLabel.h"
#include "spaceLabel.h"
#include "moveManager.h"
#include "mainDialog.h"
#include "configurator.h"

BoardDialog::BoardDialog(FDialog* parent): IDialogChain{parent} {
    setText("Board Dialog");
    setGeometry(MAIN_DIALOG_POINT, WINDOW_SIZE);
    setFocusable(false);
    board = Board::getInstance();
    LOG_F("Initialize the Board Dialog");

    // ITurn::newDebugTurns();

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            IChessman* chessman = board->getChessman(x, BOARD_LENGTH - y -1);
            if (chessman) {
                pieces[x][y] = new PieceLabel{this, Point::of(x, y)};
                addCallback(pieces[x][y], "clicked");
            } else {
                pieces[x][y] = new SpaceLabel{this, Point::of(x, y)};
            }
            addCallback(pieces[x][y], "move");
        }
    }

    // // Change this setupHook in order to trigger team color changes
    // ITurn::setupHook = [this]() {
    //     teamSignalLabels->changeTeamColor();
    // };
}

void BoardDialog::initHook() {
    moveManager = new MoveManager{this};
    teamSignalLabels = new TeamSignalLabels{this};

    if (Configurator::get(MODE) == Configurator::ONLINE) {
        LOG_F("Set up an online mode");
        ITurn::newOnlineTurns(true);
    }
    if (Configurator::get(MODE) == Configurator::OFFLINE) {
        LOG_F("Set up an offline mode");
        ITurn::newOfflineTurns(Configurator::get(TEAM) == Configurator::RED);
    }
    if (Configurator::get(MODE) == Configurator::DEBUG) {
        LOG_F("Set up an debug mode");
        ITurn::newDebugTurns();
    }

    teamSignalLabels->changeTeamColor();
    redraw();
}

void BoardDialog::initLayout() {
    FDialog::initLayout();
}

void BoardDialog::clickedCallback() {
    LOG_F("Clicked Event");
    moveManager->calculatePossibleMoves(Configurator::get(MODE) == Configurator::ONLINE);
    // debugLabel.log(pieces[moveManager->getSourcePoint()->getX()][moveManager->getSourcePoint()->getY()]->getText().toString());
    redraw();
}

void BoardDialog::moveCallback() {
    bool ret = false;

    moveManager->decorateTargetedPieces(false);
    // Swap 2 pieces in case of normal move
    ret = moveManager->movePiece(Configurator::get(MODE) == Configurator::ONLINE);
    if (ret == false)
        return;
    
    ITurn::end();
    teamSignalLabels->changeTeamColor();
}

void BoardDialog::addCallback(ILabel* label, string event) {
    label->addCallback(
        event,
        this,
        event.compare("move") == 0 ? &BoardDialog::moveCallback : &BoardDialog::clickedCallback
    );
}

void BoardDialog::dispatchChessmanMove(Point* source, Point* destination) {
    bool ret = false;

    ret = moveManager->movePiece(Configurator::get(MODE) == Configurator::ONLINE);
    if (ret == false)
        return;

    ITurn::end();
    teamSignalLabels->changeTeamColor();
}

void BoardDialog::redrawTeamSignal() {
    teamSignalLabels->changeTeamColor();
}