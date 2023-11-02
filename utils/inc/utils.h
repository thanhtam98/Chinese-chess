#pragma once

#include <algorithm>
#include <vector>

#include "utils.h"
#include "log.h"
#include "point.h"
#include "constant.h"
class Utils{
private:

public:
    static void removePointFromVector(std::vector<Point*> *pointVector, int x, int y);
    static bool isDirContainsInList(std::vector<direction_code> list, direction_code dir);
};