#ifndef NN_H
#define NN_H

#include <vector>
#include <cmath>

using namespace std;

class NN {

public:
    NN(); 

    void set( vector<std::vector<double>>& d, vector<int>& l );
    int SETtest( vector<double>& instance);
    
private:
    vector<vector<double>> setdata;
    vector<int> label;
    
    double euclideanDistance( vector<double>& a, vector<double>& b );

};

#endif // NN_H
