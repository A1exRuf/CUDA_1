#pragma once
#include <vector>
#include "Point.h"
#include "Centroid.h"

class KMeans {
private:
    int numClusters;
    int maxIters;
    int numFeatures;
    int numPoints;

    std::vector<Point> points;
    std::vector<Centroid> centroids;

    double euclideanDistance(const Point& a, const Centroid& c) const;
    void assignPointsToClusters(bool& changed);
    void recalculateCentroids();

public:
    KMeans(int clusters, int maxIterations = 100);
    void run(std::vector<Point>& data, int numFeatures);
    void printResults() const;
};
