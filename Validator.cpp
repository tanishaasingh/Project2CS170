#include "Validator.h"
#include <iostream>
using namespace std;

ModelValidator::ModelValidator(std::vector<std::vector<double>> inputData, std::vector<int> inputLabels)
    : data(inputData), labels(inputLabels) {}

double ModelValidator::performLeaveOneOutValidation(std::set<int> selectedFeatures) {
    int correctPredictions = 0;
    size_t numSamples = data.size();

    // Leave-one-out cross-validation
    for (size_t i = 0; i < numSamples; ++i) {
        std::vector<std::vector<double>> trainData;
        std::vector<int> trainLabels;

        // Prepare the training set by excluding the i-th sample
        for (size_t j = 0; j < numSamples; ++j) {
            if (j != i) {
                trainData.push_back(extractFeaturesForSample(j, selectedFeatures));
                trainLabels.push_back(labels[j]);
            }
        }

        NN neuralNetwork;
        neuralNetwork.set(trainData, trainLabels);

        std::vector<double> testSample = extractFeaturesForSample(i, selectedFeatures);
        int predictedClass = neuralNetwork.SETtest(testSample);

        if (predictedClass == labels[i]) {
            ++correctPredictions;
        }
    }

    return static_cast<double>(correctPredictions) / numSamples;
}

std::vector<double> ModelValidator::extractFeaturesForSample(int sampleIdx, std::set<int> selectedFeatures) {
    std::vector<double> selectedData;
    for (int feature : selectedFeatures) {
        selectedData.push_back(data[sampleIdx][feature - 1]);
    }
    return selectedData;
}
