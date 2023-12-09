#include "mainDialog.h"

using namespace std;

MainDialog::MainDialog(FWidget* parent) : FDialog{parent} {
    introDialog = new IntroDialog{this};
    configDialog = new ConfigDialog{this};
    boardDialog = new BoardDialog{this};
    introDialog->setNext(configDialog)
    ->setNext(boardDialog);
}

void MainDialog::initLayout() {
    FDialog::initLayout();
}