#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Point> DataLoader::loadARFF(const std::string& filename, int& M) {
    std::ifstream file(filename);
    std::vector<Point> points;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return points;
    }

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '@') continue;

        std::stringstream ss(line);
        std::string token;
        std::vector<double> values;
        while (std::getline(ss, token, ',')) {
            values.push_back(std::stod(token));
        }

        if (M == 0) M = values.size();

        Point p;
        p.coords = values;
        points.push_back(p);
    }

    return points;
}
