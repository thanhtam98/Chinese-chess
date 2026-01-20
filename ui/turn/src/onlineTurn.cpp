#include "onlineTurn.h"
#include "configurator.h"

bool OnlineTurn::_isSatisfiedTurn(team_code this_team) {
    auto configuredTeam = Configurator::get(TEAM);
    return ((configuredTeam == Configurator::RED) && (this_team == RED) && team == RED) ||
       ((configuredTeam == Configurator::BLACK) && (this_team == BLACK) && team == BLACK);
}