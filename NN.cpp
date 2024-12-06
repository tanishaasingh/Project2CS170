#include "NN.h"
#include <cmath>
#include <limits>
#include <iostream>

NN::NN() {}

void NN::train(const std::vector<std::vector<double>>& data, const std::vector<int>& labels) {
    trainingData = data;
    trainingLabels = labels;
}

int NN::test(const std::vector<double>& instance) {
    double minDistance = std::numeric_limits<double>::max();
    int predictedClass = -1;

    // Loop over all training instances to find the nearest neighbor
    for (size_t i = 0; i < trainingData.size(); ++i) {
        double dist = euclideanDistance(instance, trainingData[i]);
        if (dist < minDistance) {
            minDistance = dist;
            predictedClass = trainingLabels[i];
        }
    }

    return predictedClass;
}

double NN::euclideanDistance(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return std::sqrt(sum);
}
