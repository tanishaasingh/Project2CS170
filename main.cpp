#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

// Stub evaluation function that returns a random value
double evaluateSubset(const set<int>& subset) {
    return static_cast<double>(rand()) / RAND_MAX; // Random value between 0 and 1
}

// Forward Selection
void forwardSelection(int numFeatures) {
    set<int> currentSet; // Start with an empty set
    double bestScore = -1.0;
    cout << "Starting Forward Selection...\n";

    for (int i = 1; i <= numFeatures; ++i) {
        int bestFeature = -1;

        // Evaluate adding each unused feature
        for (int feature = 1; feature <= numFeatures; ++feature) {
            if (currentSet.find(feature) == currentSet.end()) {
                set<int> tempSet = currentSet;
                tempSet.insert(feature);

                double score = evaluateSubset(tempSet);
                cout << "Evaluating subset { ";
                for (int f : tempSet) cout << f << " ";
                score = score * 100.0;
                cout << "} => Score: " << score << "%" << endl;

                if (score > bestScore) {
                    bestScore = score;
                    bestFeature = feature;
                }
            }
        }

        if (bestFeature != -1) {
            currentSet.insert(bestFeature);
            cout << "Feature " << bestFeature << " added to the current set.\n";
        }
    }

    cout << "Finished Forward Selection.\nBest feature subset: { ";
    for (int f : currentSet) cout << f << " ";
    cout << "}" << ": accuracy is " << bestScore << "%\n";
}

// Backward Elimination
void backwardElimination(int numFeatures) {
    set<int> currentSet;
    double bestScore = -1.0;

    for (int i = 1; i <= numFeatures; ++i) currentSet.insert(i); // Start with all features

    cout << "Starting Backward Elimination...\n";

    while (currentSet.size() > 1) {
        int worstFeature = -1;

        // Evaluate removing each feature
        for (int feature : currentSet) {
            set<int> tempSet = currentSet;
            tempSet.erase(feature);

            double score = evaluateSubset(tempSet);
            cout << "Evaluating subset { ";
            for (int f : tempSet) cout << f << " ";
            score = score * 100.0;
            cout << "} => Score: " << score << "%" << endl;

            if (score > bestScore) {
                bestScore = score;
                worstFeature = feature;
            }
        }

        if (worstFeature != -1) {
            currentSet.erase(worstFeature);
            cout << "Feature " << worstFeature << " removed from the current set.\n";
        }
    }

    bestScore = bestScore * 100.0;
    cout << "Finished Backward Elimination.\nBest feature subset: { ";
    for (int f : currentSet) cout << f << " ";
    cout << "}" << ": accuracy is " << bestScore << "%\n";
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned>(time(0))); // Seed for random number generation

    int userFeatures;
    int userAlgChoice;

    cout << "Welcome to Tanishaa, Daniel and Arjun's Feature Selection Algorithm.\n";

    cout << "Please enter the total number of features: ";
    cin >> userFeatures;

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

    return 0;
}
