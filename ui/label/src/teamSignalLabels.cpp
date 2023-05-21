#include "teamSignalLabels.h"
#include "boardDialog.h"
#include "constant.h"
#include "ITurn.h"

TeamSignalLabels::TeamSignalLabels(FWidget* parent) {
    team_code turn_team = ITurn::getTurn()->getTeam();
    upper = new FLabel{parent};
    upper->setText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    upper->setForegroundColor(turn_team == BLACK ? BLACK_BG : RED_BG);
    upper->setGeometry(
        FPoint{OFFSET_X, OFFSET_Y-1},
        FSize{SPACE_BW_PIECE_X*BOARD_WIDTH, 1}
    );

    lower = new FLabel{parent};
    lower->setText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    lower->setForegroundColor(turn_team == BLACK ? BLACK_BG : RED_BG);
    lower->setGeometry(
        FPoint{OFFSET_X, BOARD_LENGTH*SPACE_BW_PIECE_Y+OFFSET_Y-1},
        FSize{SPACE_BW_PIECE_X*BOARD_WIDTH, 1}
    );
}

void TeamSignalLabels::changeTeamColor() {
    team_code turn_team = ITurn::getTurn()->getTeam();
    upper->setForegroundColor(turn_team == BLACK ? BLACK_BG : RED_BG);
    lower->setForegroundColor(turn_team == BLACK ? BLACK_BG : RED_BG);
    upper->redraw();
    lower->redraw();
}