#ifndef NN_H
#define NN_H

#include <vector>
#include <cmath>

class NN {
public:
    NN(); // Constructor to initialize the classifier
    void train(const std::vector<std::vector<double>>& data, const std::vector<int>& labels);
    int test(const std::vector<double>& instance);
    
private:
    std::vector<std::vector<double>> trainingData;
    std::vector<int> trainingLabels;
    
    double euclideanDistance(const std::vector<double>& a, const std::vector<double>& b);
};

#endif // NN_H
