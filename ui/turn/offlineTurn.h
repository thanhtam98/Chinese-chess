#pragma once
#include "ui/turn/ITurn.h"

class OfflineTurn : public ITurn {
public:
    OfflineTurn(team_code team) : ITurn(team) {};

    bool _isSatisfiedTurn(team_code this_team) override;
};