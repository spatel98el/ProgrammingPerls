// Problem statement
// Input :      File on the disc contains 10 million records, each with max 7 digits.
// Output :     Output file with all numbers sorted in increasing order
// Constraint : No memory limitation, try with CPP stdlib sort

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

int main() {
    // read file and values to vector
    ifstream datafile("./data/data_1l.txt");
    ofstream ofile("./data/ex1_sorted_data.txt");
    vector<int> inData;

    auto start = chrono::system_clock::now();

    for(int val; datafile >> val;) {
        inData.push_back(val);
    }

    // sort vector
    sort(inData.begin(), inData.end());

    //write back to out file
    for(int val : inData) {
        ofile << val << endl;
    }

    auto end = chrono::system_clock::now();
    auto diff = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Running time : " << diff.count() << endl;

    // clean up
    datafile.close();
    ofile.close();
}