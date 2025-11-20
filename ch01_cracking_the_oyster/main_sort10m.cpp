// Problem statement
// Input :      File on the disc contains 10 million records, each with max 7 digits.
// Output :     Output file with all numbers sorted in increasing order
// Constraint : Maximum 1 mb (later corrected in the text, initially this was 8m bytes) of free
//              memory available

#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <string>

// My bitmap
#include <Bitmap.hpp>
#include <SimpleProfiler.hpp>

using namespace std;

int main() {
    
    cout << "main_sort_10m:" << endl;

    int maxDataLen = 100000;

    cout << "Provide input data file path" << endl;
    string fpath;
    getline(cin, fpath);

    // create new bitmap
    auto bm = new Bitmap(maxDataLen);

    //check couple of valid bit positions
    cout << bm->getBitValue(0) << "," << bm->getBitValue(1000) << "," << bm->getBitValue(9999) << endl;

    // Read file containing intergers as string, open file for write back
    ifstream datafile(fpath);
    if(!datafile.is_open()) {
        cout << "Error in opening file : " << fpath << endl;
        return -1;
    }
    ofstream ofile("./data/sorted_data.txt");
        if(!ofile.is_open()) {
        cout << "Error in opening output file "<< endl;
        return -1;
    }

    SimpleProfiler prof;
    prof.startTimeProf();

    // go through all the bits and write back corresponding output to file
    for(int val; datafile >> val;) {
        bm->setBitPosition(val);
    }

    // sequentially iterate bit positions if bit it set write back position to the file
    for(int pos = 0; pos <= maxDataLen; pos++) {
        if(bm->getBitValue(pos))
            ofile << pos << endl;
    }

    prof.endTimeProf();
    prof.printRunningTime();

    ofile.close();
    datafile.close();
}