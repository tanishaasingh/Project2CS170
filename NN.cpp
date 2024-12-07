#include "NN.h"
#include <cmath>
#include <limits>
#include <iostream>

using namespace std;

NN::NN() {}

void NN::set(vector<std::vector<double>>& d, vector<int>& l) {

    setdata = d;
    label = l;

}

int NN::SETtest(vector<double>& instance) {

    double MIN = numeric_limits<double>::max();
    int p = -1;

   
    for (size_t i = 0; i < setdata.size(); ++i) {
        double dist = euclideanDistance(instance, setdata[i]);

        if (dist < MIN) {


            MIN = dist;
            p = label[i];

        }
    }

    return p;
}

double NN::euclideanDistance(vector<double>& a, vector<double>& b) {

    double total = 0;
    for (size_t i = 0; i < a.size(); i++) {

        total =  total + (a[i] - b[i]) * (a[i] - b[i]);

    }
    return sqrt(total);
}
