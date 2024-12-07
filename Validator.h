#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <vector>
#include <set>
#include "NN.h"

class ModelValidator {
public:
    ModelValidator(vector<vector<double>> inputData, vector<int> inputLabels);

    double performLeaveOneOutValidation(set<int> selectedFeatures);


private:

    vector<vector<double>> data;
    vector<int> labels;
    
     std::vector<double> extractFeaturesForSample(int sampleIdx, std::set<int> selectedFeatures);

};

#endif // VALIDATOR_H

