#pragma once
#include "ITurn.h"
#include "log.h"

class OnlineTurn : public ITurn {
public:
    explicit OnlineTurn(team_code team) : ITurn(team) {
        LOG_F("ONLINE MODE");
    }

    bool _isSatisfiedTurn(team_code this_team) override;
};