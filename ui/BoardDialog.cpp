#include "ui/BoardDialog.h"
#include "logic/board.h"
#include "logic/iChessman.h"
#include "utils/constant.h"

using namespace std;

BoardDialog::BoardDialog(FWidget* parent) : FDialog{parent} {
    board = Board::getInstance();
    cout << "Init board" << endl;

    for (int x = 0; x < BOARD_LENGTH; x++) {
        for (int y = 0; y < BOARD_WIDTH; y++) {
            pieces[x][y] = new FButton{this};
        }
    }
}

void BoardDialog::initLayout() {
    cout << "Init layout" << endl;
    mapFromBoard();
    FDialog::initLayout();
}

void BoardDialog::mapFromBoard() {
    for (int x = 0; x < BOARD_LENGTH; x++) {
        for (int y = 0; y < BOARD_WIDTH; y++) {
            cout << "Set up [" << x << ";" << y << "] " << endl;
            IChessman* chessman = board->getChessman(x, y);
            FButton* button = pieces[x][y];
            button->setParent(this);
            button->setShadow(false);
            button->setClickAnimation(false);

            if (chessman != nullptr) {
                team_code team = chessman->getTeam();
                button->setBackgroundColor(team == BLACK ? BLACK_BG : RED_BG);
                button->setFocusBackgroundColor(team == BLACK ? FOCUS_BLACK_BG : FOCUS_RED_BG);
                button->setText("Y");
            }
            button->setGeometry(FPoint{x*5+1, y*2+1}, FSize{4,1});

        }
    }
}