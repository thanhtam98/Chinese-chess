#include "mainDialog.h"

using namespace std;

MainDialog::MainDialog(FWidget* parent) : FDialog{parent} {
    setText("Main Dialog");
    introDialog = new IntroDialog{this};
    configDialog = new ConfigDialog{this};
    boardDialog = new BoardDialog{this};
    introDialog->setNext(configDialog)->setNext(boardDialog);
}

void MainDialog::initLayout() {
    FDialog::initLayout();
}