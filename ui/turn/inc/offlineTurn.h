#pragma once
#include "ITurn.h"
#include "log.h"

class OfflineTurn : public ITurn {
public:
    OfflineTurn(team_code team) : ITurn(team) {
        LOG_F("OFFLINE MODE");
    };

    bool _isSatisfiedTurn(team_code this_team) override;
};