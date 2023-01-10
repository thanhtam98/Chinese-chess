#pragma once
#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "logic/iBoard.h"

class MockBoard : public IBoard{
public:
    MOCK_METHOD(bool, isOccupied, (int x, int y), (override));
    MOCK_METHOD(IChessman*, getChessman, (int x, int y), (override));

};