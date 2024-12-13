#include "NN.h"
#include "Validator.h"
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>

using namespace std;

ModelValidator* validator = nullptr; // Global pointer to access ModelValidator instance

// Real evaluation function using leave-one-out validation
double evaluateSubset(const set<int>& subset) {
    if (validator == nullptr) {
        cerr << "Error: ModelValidator is not initialized!" << endl;
        return 0.0;
    }
    return validator->performLeaveOneOutValidation(subset);
}

// Forward Selection
void forwardSelection(int numFeatures) {
    set<int> currentSet; 
    double overallBestScore = -1.0;
    set<int> bestSubset;

    cout << "Starting Forward Selection...\n";

    for (int i = 1; i <= numFeatures; ++i) {
        int bestFeature = -1;
        double iterationBestScore = -1.0;

        for (int feature = 1; feature <= numFeatures; ++feature) {
            if (currentSet.find(feature) == currentSet.end()) {
                set<int> tempSet = currentSet;
                tempSet.insert(feature);

                double score = evaluateSubset(tempSet);
                cout << "Evaluating subset { ";
                for (int f : tempSet) cout << f << " ";
                cout << "} => Score: " << score * 100.0 << "%" << endl;

                if (score > iterationBestScore) {
                    iterationBestScore = score;
                    bestFeature = feature;
                }
            }
        }

        if (bestFeature != -1 && iterationBestScore > overallBestScore) {
            currentSet.insert(bestFeature);
            overallBestScore = iterationBestScore;
            bestSubset = currentSet;
            cout << "Feature " << bestFeature << " added to the current set.\n";
        } else {
            break; // No improvement; terminate early
        }
    }

    cout << "Finished Forward Selection.\nBest feature subset: { ";
    for (int f : bestSubset) cout << f << " ";
    cout << "}: accuracy is " << overallBestScore * 100.0 << "%\n";
}



// Backward Elimination
void backwardElimination(int numFeatures) {
    set<int> currentSet;
    double overallBestScore = -1.0;
    set<int> bestSubset;

    for (int i = 1; i <= numFeatures; ++i) currentSet.insert(i); 

    cout << "Starting Backward Elimination...\n";

    while (currentSet.size() > 1) {
        int worstFeature = -1;
        double iterationBestScore = -1.0;

        for (int feature : currentSet) {
            set<int> tempSet = currentSet;
            tempSet.erase(feature);

            double score = evaluateSubset(tempSet);
            cout << "Evaluating subset { ";
            for (int f : tempSet) cout << f << " ";
            cout << "} => Score: " << score * 100.0 << "%" << endl;

            if (score > iterationBestScore) {
                iterationBestScore = score;
                worstFeature = feature;
            }
        }

        if (worstFeature != -1 && iterationBestScore > overallBestScore) {
            currentSet.erase(worstFeature);
            overallBestScore = iterationBestScore;
            bestSubset = currentSet;
            cout << "Feature " << worstFeature << " removed from the current set.\n";
        } else {
            break; // No improvement; terminate early
        }
    }

    cout << "Finished Backward Elimination.\nBest feature subset: { ";
    for (int f : bestSubset) cout << f << " ";
    cout << "}: accuracy is " << overallBestScore * 100.0 << "%\n";
}



void readDataset(const string& filename, vector<vector<double>>& data, vector<int>& labels) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        double value;
        int label;
        ss >> label; 
        labels.push_back(label);

        vector<double> features;
        while (ss >> value) {
            features.push_back(value);
        }
        data.push_back(features);
    }
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned>(time(0))); // Seed for random number generation

    int userFeatures;
    int userAlgChoice;

    cout << "Welcome to Tanishaa, Daniel, and Arjun's Feature Selection Algorithm.\n";
    cout << "Please enter the total number of features: ";
    cin >> userFeatures;

    vector<vector<double>> data;
    vector<int> labels;
    
    
    cout << "\n Please enter the dataset filename (e.g., small-test-dataset.txt): \n";

    string filename;
    cin >> filename;
    readDataset(filename, data, labels);

    // Initialize ModelValidator with the dataset
    ModelValidator modelValidator(data, labels);
    validator = &modelValidator;

    cout << "Type the number of the algorithm you want to run.\n";
    cout << "   1. Forward Selection\n";
    cout << "   2. Backward Elimination\n";
    cout << "   3. Our Special Algorithm (Not implemented yet)\n";
    cin >> userAlgChoice;

    if (userAlgChoice == 1) {
        forwardSelection(userFeatures);
    } else if (userAlgChoice == 2) {
        backwardElimination(userFeatures);
    } else {
        cout << "Special Algorithm is not implemented yet.\n";
    }

    cout << endl; 
    cout << endl;
    cout << endl;

    cout << "NOW Checking the datasets:\n ";

    
    set<int> SUBSET = {3, 5, 7}; 
    set<int> SUBSET2 = {1, 15, 27}; 
    set<int> SUBSET3 = {3998,4000, 4001}; 


    ModelValidator ModelValidator(data, labels);

    double A = ModelValidator.performLeaveOneOutValidation(SUBSET);
    double B = ModelValidator.performLeaveOneOutValidation(SUBSET2);
    double C = ModelValidator.performLeaveOneOutValidation(SUBSET3);

    cout << "Leave-One-Out validation accuracy with features {3, 5, 7}: " << A * 100 << "%" << endl;
    cout << " Leave-One-Out validation accuracy with features {1, 15, 27}: " << B * 100 << "%" << endl;
    cout << " (Titanic) Leave-One-Out validation accuracy with features {3998, 4000, 4001}: " << B * 100 << "%" << endl;
 
    return 0;
}