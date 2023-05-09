#pragma once
#include "ui/turn/ITurn.h"

class DebugTurn : public ITurn {
public:
    DebugTurn() : ITurn{T_NONE} {};

    bool _isSatisfiedTurn(team_code this_team) override;
};