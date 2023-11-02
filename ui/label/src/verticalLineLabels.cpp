#include "verticalLineLabels.h"
#include "mainDialog.h"

VerticleLineLabels::VerticleLineLabels(FWidget* parent) {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH-1; j++) {
            int vert = j;
            if (j == BOARD_LENGTH/2-1) continue;
            if (j > BOARD_LENGTH/2-1) vert = j - 1;
            verticalLines[i][vert] = new FLabel{parent};
            verticalLines[i][vert]->setText("│");
            verticalLines[i][vert]->setGeometry(
                FPoint{i*SPACE_BW_PIECE_X+2, j*SPACE_BW_PIECE_Y+OFFSET_Y+1},
                FSize{1,1}
            );
        }
    }

    // Draw vertical lines in the border
    verticalLinesAtBorder[0] = new FLabel{parent};
    verticalLinesAtBorder[0]->setText("│");
    verticalLinesAtBorder[0]->setGeometry(
        FPoint{2, (BOARD_LENGTH/2-1)*SPACE_BW_PIECE_Y+OFFSET_Y+1}, 
        FSize{1, 1}
    );

    verticalLinesAtBorder[1] = new FLabel{parent};
    verticalLinesAtBorder[1]->setText("│");
    verticalLinesAtBorder[1]->setGeometry(
        FPoint{(BOARD_WIDTH-1)*SPACE_BW_PIECE_X+2, (BOARD_LENGTH/2-1)*SPACE_BW_PIECE_Y+OFFSET_Y+1}, 
        FSize{1, 1}
    );
}