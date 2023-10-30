#pragma once
#include "ITurn.h"
#include "log.h"

class DebugTurn : public ITurn {
public:
    DebugTurn() : ITurn{T_NONE} {
        LOG_F("DEBUG MODE");
    };

    bool _isSatisfiedTurn(team_code this_team) override;
};