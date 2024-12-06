#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <vector>
#include <set>
#include "NN.h"

class Validator {
public:
    Validator(const std::vector<std::vector<double>>& data, const std::vector<int>& labels);
    double leaveOneOutValidation(const std::set<int>& featureSubset);

private:
    std::vector<std::vector<double>> dataset;
    std::vector<int> labels;

    std::vector<double> getFeaturesForInstance(int instanceIdx, const std::set<int>& featureSubset);
};

#endif // VALIDATOR_H
