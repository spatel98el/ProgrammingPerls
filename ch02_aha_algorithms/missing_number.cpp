// Probelm statement:
// Given a sequential file that contains at most four billion 32 bit integers in random
// order. Atleast one integer is missing from it. We need to find this missing number. 

// for simplicity, tackling this problem with smaller dataset of 10000 integers

// use binary search to track the range

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {

    ifstream fin("./data/data_10k.txt");

    // based on E. Reingold's solution need to iterate on bit positions
    // then track the range, one with smaller range having missing number
    // Try for 32 bit number range
    // use two vectors to track range
    vector<int> rangeTracker[2];

    // read file in the vec 0
    int data = 0;
    while(cin >> data) {
        rangeTracker[0].push_back(data);
    }

    unsigned int bitMask = 0x80000000;
    vector<int> &rangeVec;
    for (int i = 0, data = 0; i < 32; i++, bitMask >>= 1)
    {

        while (cin >> data)
        {
            if (data & bitMask)
            {
                // store in verc 0
                rangeTracker[0].push_back(data);
            }
            else
            {
                // store in vec 1
                rangeTracker[1].push_back(data);
            }
        }

        // move ref vector to smaller range
        if(rangeTracker[0].size() >  rangeTracker[1].size()) {
            rangeVec = rangeTracker[1];
        } else {
            rangeVec = rangeTracker[0];
        }
    }
}