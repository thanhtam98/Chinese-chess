#pragma once 
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "logic/iBoard.h"

class MockChessman : public IChessman{
    MOCK_METHOD(std::vector <Point*>, getPossibleMoves, (Point *point), (override));
    MOCK_METHOD(bool, move, (Point *point), (override));
    MOCK_METHOD(team_code, getTeam, (), (override));
};