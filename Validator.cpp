#include "Validator.h"
#include <iostream>

Validator::Validator(const std::vector<std::vector<double>>& data, const std::vector<int>& labels) 
    : dataset(data), labels(labels) {}

double Validator::leaveOneOutValidation(const std::set<int>& featureSubset) {
    int correctPredictions = 0;
    size_t totalInstances = dataset.size();

    // Leave-one-out cross-validation
    for (size_t i = 0; i < totalInstances; ++i) {
        std::vector<std::vector<double>> trainingData;
        std::vector<int> trainingLabels;

        // Prepare the training set by excluding the i-th instance
        for (size_t j = 0; j < totalInstances; ++j) {
            if (j != i) {
                trainingData.push_back(getFeaturesForInstance(j, featureSubset));
                trainingLabels.push_back(labels[j]);
            }
        }

        NN nn;
        nn.train(trainingData, trainingLabels);

        // Test the model with the i-th instance
        std::vector<double> testInstance = getFeaturesForInstance(i, featureSubset);
        int predictedClass = nn.test(testInstance);

        // Check if the prediction is correct
        if (predictedClass == labels[i]) {
            ++correctPredictions;
        }
    }

    // Calculate accuracy
    return static_cast<double>(correctPredictions) / totalInstances;
}

std::vector<double> Validator::getFeaturesForInstance(int instanceIdx, const std::set<int>& featureSubset) {
    std::vector<double> selectedFeatures;
    for (int feature : featureSubset) {
        selectedFeatures.push_back(dataset[instanceIdx][feature - 1]); // feature index is 1-based
    }
    return selectedFeatures;
}
