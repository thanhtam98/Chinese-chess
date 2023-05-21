#pragma once 
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "iBoard.h"
#include "constant.h"

class MockChessman : public IChessman{
public:
    MOCK_METHOD(std::vector <Point*>, getPossibleMoves, (), (override));
    MOCK_METHOD(bool, move, (Point *point), (override));
    MOCK_METHOD(team_code, getTeam, (), (override));
    MOCK_METHOD(chessman_code, getCode, (), (override));
    MOCK_METHOD(string, getName, (), (override));
};