#pragma once

#include "utils/point.h"
#include <algorithm>
#include <vector>
class Utils{
private:

public:
    static void removePointFromVector(std::vector<Point*> *pointVector, int x, int y);
    static bool isDirContainsInList(std::vector<direction_code> list, direction_code dir);
};