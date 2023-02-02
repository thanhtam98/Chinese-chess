#pragma once 
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "logic/iBoard.h"
#include "utils/constant.h"

class MockChessman : public IChessman{
public:
    MOCK_METHOD(std::vector <Point*>, getPossibleMoves, (), (override));
    MOCK_METHOD(bool, move, (Point *point), (override));
    MOCK_METHOD(team_code, getTeam, (), (override));
    MOCK_METHOD(chessman_code, getCode, (), (override));
};