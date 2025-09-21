#pragma once
#include <vector>
#include <string>
#include "Point.h"

class DataLoader {
public:
    static std::vector<Point> loadARFF(const std::string& filename, int& M);
};