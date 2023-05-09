#include "ui/label/debugLabel.h"
#include "ui/boardDialog.h"
#include "utils/constant.h"

DebugLabel::DebugLabel(FWidget* parent) {
    debug = new FLabel{parent};
    debug->setText("DEBUG:");
    debug->setGeometry(
        FPoint{OFFSET_X, BOARD_LENGTH*SPACE_BW_PIECE_Y+OFFSET_Y},
        FSize{SPACE_BW_PIECE_X*BOARD_WIDTH, 1}
    );
}

void DebugLabel::log(std::string content) {
    debug->clear();
    debug->setText("DEBUG: " + content);
    debug->redraw();
}