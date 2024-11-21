#include <iostream> 
#include <algorithm>
#include <string> 
#include <vector> 


using namespace std; 

int main(int argc, char* argv[]) {

    int userfeatures; 
    int useralgchoice; 

    cout << "Welcome to Tanishaa, Daniel and Arjun's " ; 
    cout << "Feature Selection Algorithm." << endl; 

    cout << "Please enter the total number of features: " ; 
    cin >> userfeatures; 

    cout << "Type the number of the algorithm you want to run." << endl; 
    cout << "   1. Forward Selection" << endl; 
    cout << "   2. Backward Elimination" << endl; 
    cout << "   3. Our Special Algoritm" << endl; 
    cin >> useralgchoice; 

    

    return 0; 
}