#pragma once
#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "iBoard.h"

class MockBoard : public IBoard{
public:
    MOCK_METHOD(bool, isOccupied, (int x, int y), (override));
    MOCK_METHOD(bool, isOccupied, (Point *point), (override));
    MOCK_METHOD(IChessman*, getChessman, (int x, int y), (override));
    MOCK_METHOD(IChessman*, getChessman, (Point *point), (override));
    MOCK_METHOD(void, move, (Point* from, Point* to), (override));
    MOCK_METHOD(std::vector<Point*>, getPossibleMoves, (Point* target), (override));
};