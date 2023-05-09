#include "ui/label/horizontalLabels.h"
#include "ui/boardDialog.h"

HorizontalLineLabels::HorizontalLineLabels(FWidget* parent) {
    for (int i = 0; i < BOARD_WIDTH-1; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            horizontalLines[i][j] = new FLabel{parent};
            horizontalLines[i][j]->setText("───");
            horizontalLines[i][j]->setGeometry(
                FPoint{i*SPACE_BW_PIECE_X+OFFSET_X+PIECE_SIZE_X, j*SPACE_BW_PIECE_Y+OFFSET_Y},
                FSize{SPACE_LABEL_SIZE_X,SPACE_LABEL_SIZE_Y}
            );
            horizontalLines[i][j]->back();
        }
    }
}