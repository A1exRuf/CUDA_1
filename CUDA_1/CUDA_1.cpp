#include <iostream>
#include "DataLoader.h"
#include "KMeans.h"

int main() {
    setlocale(LC_ALL, "Russian");

    const std::string inputFile = "160k5.arff";
    int numFeatures = 0;
    std::vector<Point> dataset = DataLoader::loadARFF(inputFile, numFeatures);

    if (dataset.empty()) {
        std::cerr << "������: �� ������� ��������� ������ �� ����� " << inputFile << "\n";
        return 1;
    }

    std::cout << "���� ��������: " << dataset.size()
        << " ��������, " << numFeatures << " ���������.\n";

    const int numClusters = 6;
    const int maxIterations = 100;

    KMeans kmeans(numClusters, maxIterations);
    kmeans.run(dataset, numFeatures);
    kmeans.printResults();

    return 0;
}
