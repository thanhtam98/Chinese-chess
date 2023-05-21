#include "riverBorderLabels.h"
#include "constant.h"
#include "boardDialog.h"

RiverBorderLabels::RiverBorderLabels(FWidget* parent) {
    label1 = new FLabel{"楚", parent};
    label1->setGeometry(
        FPoint{OFFSET_X+SPACE_BW_PIECE_X, (BOARD_LENGTH/2)*SPACE_BW_PIECE_Y + OFFSET_Y-1},
        FSize{2,1}
    );
    label2 = new FLabel{"河", parent};
    label2->setGeometry(
        FPoint{OFFSET_X+SPACE_BW_PIECE_X*2, (BOARD_LENGTH/2)*SPACE_BW_PIECE_Y + OFFSET_Y-1},
        FSize{2,1}
    );
    label3 = new FLabel{"漢", parent};
    label3->setGeometry(
        FPoint{OFFSET_X+SPACE_BW_PIECE_X*6, (BOARD_LENGTH/2)*SPACE_BW_PIECE_Y + OFFSET_Y-1},
        FSize{2,1}
    );
    label4 = new FLabel{"界", parent};
    label4->setGeometry(
        FPoint{OFFSET_X+SPACE_BW_PIECE_X*7, (BOARD_LENGTH/2)*SPACE_BW_PIECE_Y + OFFSET_Y-1},
        FSize{2,1}
    );
}