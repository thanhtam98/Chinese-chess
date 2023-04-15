#include "ui/BoardDialog.h"
#include "logic/board.h"
#include "logic/iChessman.h"
#include "utils/constant.h"
#include "ui/button/spaceButtonText.h"

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
    initOtherBoardItems();
    initChessmanFromBoard();
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
            } else {
                button->setBackgroundColor(FColor::White);
                button->setFocusBackgroundColor(FColor::Grey93);
                button->setText(SpaceButtonText::getText(x, y));
                button->setForegroundColor(FColor::Black);
            }
            // button->ignorePadding();
            // button->setLeftPadding(-1);
            button->front();
            button->setGeometry(
                FPoint{x*SPACE_BW_PIECE_X+OFFSET_X, y*SPACE_BW_PIECE_Y+OFFSET_Y},
                FSize{PIECE_SIZE_X,PIECE_SIZE_Y}
            );
        }
    }
}
void BoardDialog::initOtherBoardItems() {
    // Draw the border
    riverBoundaryLabel = new FLabel{this};
    riverBoundaryLabel->setText("楚   河                  漢   界");
    riverBoundaryLabel->setGeometry(FPoint{7, BOARD_LENGTH}, FSize{35,1});
    // Draw the horizontal lines
    for (int i = 0; i < BOARD_WIDTH-1; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            horizontalLines[i][j] = new FLabel{this};
            horizontalLines[i][j]->setText("─");
            horizontalLines[i][j]->setGeometry(
                FPoint{i*SPACE_BW_PIECE_X+SPACE_BW_PIECE_X, j*SPACE_BW_PIECE_Y+1},
                FSize{SPACE_LABEL_SIZE_X,SPACE_LABEL_SIZE_Y}
            );
            horizontalLines[i][j]->back();
        }
    }

    // Draw the vertical lines
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH-1; j++) {
            int vert = j;
            if (j == BOARD_LENGTH/2-1) continue;
            if (j > BOARD_LENGTH/2-1) vert = j - 1;
            verticalLines[i][vert] = new FLabel{this};
            verticalLines[i][vert]->setText("│");
            verticalLines[i][vert]->setGeometry(
                FPoint{i*SPACE_BW_PIECE_X+2, j*SPACE_BW_PIECE_Y+2},
                FSize{1,1}
            );
        }
    }

    // Draw vertical lines in the border
    verticalLinesAtBorder[0] = new FLabel{this};
    verticalLinesAtBorder[0]->setText("│");
    verticalLinesAtBorder[0]->setGeometry(
        FPoint{2, (BOARD_LENGTH/2-1)*SPACE_BW_PIECE_Y+2}, 
        FSize{1, 1}
    );

    verticalLinesAtBorder[1] = new FLabel{this};
    verticalLinesAtBorder[1]->setText("│");
    verticalLinesAtBorder[1]->setGeometry(
        FPoint{(BOARD_WIDTH-1)*SPACE_BW_PIECE_X+2, (BOARD_LENGTH/2-1)*SPACE_BW_PIECE_Y+2}, 
        FSize{1, 1}
    );

    // Draw the fortress lines
    fortressLines[0][0] = new FLabel{this};
    fortressLines[0][0]->setText("╲");
    fortressLines[0][0]->setGeometry(
        FPoint{(BOARD_WIDTH-5)*SPACE_BW_PIECE_X, 2}, 
        FSize{1,1}
    );

    fortressLines[0][1] = new FLabel{this};
    fortressLines[0][1]->setText("╱");
    fortressLines[0][1]->setGeometry(
        FPoint{(BOARD_WIDTH-4)*SPACE_BW_PIECE_X, 2}, 
        FSize{1,1}
    );

    fortressLines[0][2] = new FLabel{this};
    fortressLines[0][2]->setText("╲");
    fortressLines[0][2]->setGeometry(
        FPoint{(BOARD_WIDTH-4)*SPACE_BW_PIECE_X, SPACE_BW_PIECE_Y+2}, 
        FSize{1,1}
    );

    fortressLines[0][3] = new FLabel{this};
    fortressLines[0][3]->setText("╱");
    fortressLines[0][3]->setGeometry(
        FPoint{(BOARD_WIDTH-5)*SPACE_BW_PIECE_X, SPACE_BW_PIECE_Y+2}, 
        FSize{1,1}
    );

    fortressLines[1][0] = new FLabel{this};
    fortressLines[1][0]->setText("╲");
    fortressLines[1][0]->setGeometry(
        FPoint{(BOARD_WIDTH-5)*SPACE_BW_PIECE_X, 7*SPACE_BW_PIECE_Y+2}, 
        FSize{1,1}
    );

    fortressLines[1][1] = new FLabel{this};
    fortressLines[1][1]->setText("╱");
    fortressLines[1][1]->setGeometry(
        FPoint{(BOARD_WIDTH-4)*SPACE_BW_PIECE_X, 7*SPACE_BW_PIECE_Y+2}, 
        FSize{1,1}
    );

    fortressLines[1][2] = new FLabel{this};
    fortressLines[1][2]->setText("╲");
    fortressLines[1][2]->setGeometry(
        FPoint{(BOARD_WIDTH-4)*SPACE_BW_PIECE_X, 8*SPACE_BW_PIECE_Y+2}, 
        FSize{1,1}
    );

    fortressLines[1][3] = new FLabel{this};
    fortressLines[1][3]->setText("╱");
    fortressLines[1][3]->setGeometry(
        FPoint{(BOARD_WIDTH-5)*SPACE_BW_PIECE_X, 8*SPACE_BW_PIECE_Y+2}, 
        FSize{1,1}
    );
}