#include "KMeans.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <chrono>

KMeans::KMeans(int clusters, int maxIterations)
    : numClusters(clusters), maxIters(maxIterations) {
    srand(static_cast<unsigned>(time(nullptr)));
}

double KMeans::euclideanDistance(const Point& a, const Centroid& c) const {
    double sum = 0.0;
    for (size_t i = 0; i < a.coords.size(); i++) {
        double diff = a.coords[i] - c.coords[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

void KMeans::assignPointsToClusters(bool& changed) {
    changed = false;

    for (auto& p : points) {
        double bestDist = std::numeric_limits<double>::max();
        int bestCluster = -1;

        for (int k = 0; k < numClusters; k++) {
            double dist = euclideanDistance(p, centroids[k]);
            if (dist < bestDist) {
                bestDist = dist;
                bestCluster = k;
            }
        }

        if (p.cluster != bestCluster) {
            changed = true;
            p.cluster = bestCluster;
        }
    }
}

void KMeans::recalculateCentroids() {
    std::vector<std::vector<double>> newCoords(numClusters, std::vector<double>(numFeatures, 0.0));
    std::vector<int> clusterSizes(numClusters, 0);

    for (auto& p : points) {
        clusterSizes[p.cluster]++;
        for (int j = 0; j < numFeatures; j++) {
            newCoords[p.cluster][j] += p.coords[j];
        }
    }

    for (int k = 0; k < numClusters; k++) {
        if (clusterSizes[k] == 0) continue;
        for (int j = 0; j < numFeatures; j++) {
            centroids[k].coords[j] = newCoords[k][j] / clusterSizes[k];
        }
    }
}

void KMeans::run(std::vector<Point>& data, int numFeatures) {
    this->points = data;
    this->numFeatures = numFeatures;
    this->numPoints = static_cast<int>(data.size());

    centroids.resize(numClusters);
    for (int k = 0; k < numClusters; k++) {
        centroids[k].coords = points[rand() % numPoints].coords;
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int iter = 0; iter < maxIters; iter++) {
        bool changed = false;

        assignPointsToClusters(changed);
        recalculateCentroids();

        if (!changed) break;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Время выполнения: " << duration.count() << " секунд\n";
}

void KMeans::printResults() const {
    for (int k = 0; k < numClusters; k++) {
        int count = 0;
        for (auto& p : points)
            if (p.cluster == k) count++;
        std::cout << "Кластер " << k << ": " << count << " объектов\n";
    }
}
