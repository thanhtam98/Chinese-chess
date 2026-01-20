#include "teamSignalLabels.h"
#include "boardDialog.h"
#include "ITurn.h"
#include "configurator.h"

TeamSignalLabels::TeamSignalLabels(FWidget* parent) {
    bool isTurnSetUp = true;
    team_code turn_team = T_NONE;
    if (ITurn::get() == nullptr) {
        isTurnSetUp = false; 
    } else {
        turn_team = ITurn::get()->getTeam();
    }
    FColor teamColor = getTeamBgColor(turn_team);
    upper = new FLabel{parent};
    upper->setText("████████████████████████████████████████████");
    upper->setForegroundColor(teamColor);
    upper->setGeometry(
        FPoint{OFFSET_X, OFFSET_Y-2},
        FSize{SPACE_BW_PIECE_X*BOARD_WIDTH, 1}
    );

    lower = new FLabel{parent};
    lower->setText("████████████████████████████████████████████");
    lower->setForegroundColor(teamColor);
    lower->setGeometry(
        FPoint{OFFSET_X, BOARD_LENGTH*SPACE_BW_PIECE_Y+OFFSET_Y},
        FSize{SPACE_BW_PIECE_X*BOARD_WIDTH, 1}
    );
}

void TeamSignalLabels::changeTeamColor() {
    team_code turn_team = ITurn::get()->getTeam();
    if (Configurator::get(MODE) == Configurator::ONLINE) {
        auto configuredTeam = Configurator::get(TEAM);
        if ((configuredTeam == Configurator::RED && turn_team == BLACK) ||
            (configuredTeam == Configurator::BLACK && turn_team == RED)) {
                turn_team = T_NONE;
            }
    }
    FColor teamColor = getTeamBgColor(turn_team);
    upper->setForegroundColor(teamColor);
    lower->setForegroundColor(teamColor);
    upper->redraw();
    lower->redraw();
}

FColor TeamSignalLabels::getTeamBgColor(team_code turn_team) {
    switch (turn_team) {
        case RED:
            return RED_BG;
        case BLACK:
            return BLACK_BG;
        case T_NONE:
        default:
            return NOTEAM_BG;
    }
}