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
    introDialog = new IntroDialog{this};
    boardDialog = new BoardDialog{this};
    introDialog->setNext(boardDialog);
}

void MainDialog::initLayout() {
    FDialog::initLayout();
}