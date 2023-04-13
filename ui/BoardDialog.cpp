#include "ui/BoardDialog.h"
#include "logic/board.h"
#include "logic/iChessman.h"
#include "utils/constant.h"

using namespace std;

BoardDialog::BoardDialog(FWidget* parent) : FDialog{parent} {
    board = Board::getInstance();
    cout << "Init board" << endl;

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            pieces[x][y] = new FButton{this};
        }
    }
}

void BoardDialog::initLayout() {
    // cout << "Init layout" << endl;
    initChessmanFromBoard();
    initOtherBoardItems();
    FDialog::initLayout();
}

void BoardDialog::initChessmanFromBoard() {
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            // cout << "Set up [" << x << ";" << y << "] " << endl;
            IChessman* chessman = board->getChessman(x, BOARD_LENGTH - y -1);
            FButton* button = pieces[x][y];
            button->setShadow(false);
            button->setClickAnimation(false);

            if (chessman != nullptr) {
                team_code team = chessman->getTeam();
                button->setBackgroundColor(team == BLACK ? BLACK_BG : RED_BG);
                button->setFocusBackgroundColor(team == BLACK ? FOCUS_BLACK_BG : FOCUS_RED_BG);
                button->setText(chessman->getName());
            }
            button->setGeometry(FPoint{x*5+1, y*2+1}, FSize{4,1});

        }
    }
}
void BoardDialog::initOtherBoardItems() {
    FLabel *riverBoundaryLabel = new FLabel{this};
    riverBoundaryLabel->setText("楚  河         漢  界");
    riverBoundaryLabel->setGeometry(FPoint{12, BOARD_LENGTH}, FSize{30,1});

}