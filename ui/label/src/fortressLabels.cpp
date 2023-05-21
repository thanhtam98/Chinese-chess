#include "fortressLabels.h"
#include "boardDialog.h"

FortressLabels::FortressLabels(FWidget* parent) {
    fortressLines[0][0] = new FLabel{parent};
    fortressLines[0][0]->setText("╲");
    fortressLines[0][0]->setGeometry(
        FPoint{(BOARD_WIDTH-5)*SPACE_BW_PIECE_X, OFFSET_Y+1}, 
        FSize{1,1}
    );

    fortressLines[0][1] = new FLabel{parent};
    fortressLines[0][1]->setText("╱");
    fortressLines[0][1]->setGeometry(
        FPoint{(BOARD_WIDTH-4)*SPACE_BW_PIECE_X-1, OFFSET_Y+1}, 
        FSize{1,1}
    );

    fortressLines[0][2] = new FLabel{parent};
    fortressLines[0][2]->setText("╲");
    fortressLines[0][2]->setGeometry(
        FPoint{(BOARD_WIDTH-4)*SPACE_BW_PIECE_X-1, SPACE_BW_PIECE_Y+OFFSET_Y+1}, 
        FSize{1,1}
    );

    fortressLines[0][3] = new FLabel{parent};
    fortressLines[0][3]->setText("╱");
    fortressLines[0][3]->setGeometry(
        FPoint{(BOARD_WIDTH-5)*SPACE_BW_PIECE_X, SPACE_BW_PIECE_Y+OFFSET_Y+1}, 
        FSize{1,1}
    );

    fortressLines[1][0] = new FLabel{parent};
    fortressLines[1][0]->setText("╲");
    fortressLines[1][0]->setGeometry(
        FPoint{(BOARD_WIDTH-5)*SPACE_BW_PIECE_X, 7*SPACE_BW_PIECE_Y+OFFSET_Y+1}, 
        FSize{1,1}
    );

    fortressLines[1][1] = new FLabel{parent};
    fortressLines[1][1]->setText("╱");
    fortressLines[1][1]->setGeometry(
        FPoint{(BOARD_WIDTH-4)*SPACE_BW_PIECE_X-1, 7*SPACE_BW_PIECE_Y+OFFSET_Y+1}, 
        FSize{1,1}
    );

    fortressLines[1][2] = new FLabel{parent};
    fortressLines[1][2]->setText("╲");
    fortressLines[1][2]->setGeometry(
        FPoint{(BOARD_WIDTH-4)*SPACE_BW_PIECE_X-1, 8*SPACE_BW_PIECE_Y+OFFSET_Y+1}, 
        FSize{1,1}
    );

    fortressLines[1][3] = new FLabel{parent};
    fortressLines[1][3]->setText("╱");
    fortressLines[1][3]->setGeometry(
        FPoint{(BOARD_WIDTH-5)*SPACE_BW_PIECE_X, 8*SPACE_BW_PIECE_Y+OFFSET_Y+1}, 
        FSize{1,1}
    );
}