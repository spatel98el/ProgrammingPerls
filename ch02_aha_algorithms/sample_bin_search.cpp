// This is not the part of the book but warm up 
// generate simple vector of random data, sort and search 

#include <vector>
#include <algorithm>
#include <iostream>

#include <Datagen.hpp>
#include <SimpleProfiler.hpp>

using namespace std;

bool binarySearch(vector<int> a, int key) {
    int low = 0, high = a.size(), mid = 0;
    int iter = 0;
    while(low < high) {
        mid = (high + low)/2;
        // cout << "Iter:" << iter << ", low:" << low << ", high:" << high << ", mid:" << mid << ", a[mid]:" << a[mid] << endl;
        if(a[mid] > key)
            // search left range
            high = mid - 1;
        else if (a[mid] < key)
            // search right range
            low = mid + 1;
        else
            return true;

     }

     return false;
}

bool binarySearchRecursive(vector<int> &a, int low, int high, int key) {
    if (low >= high)
        // can not find
        return false;

    int mid = (low + high)/2;
    if(a[mid] > key) {
        // left subarray
        return (binarySearchRecursive(a, low, mid-1, key));
    } else if (a[mid] < key) {
        // right subarray
        return (binarySearchRecursive(a, mid+1, high, key));
    } else {
        // found it
        return true;
    }
}

int main() {

    // fill temp data
    vector<int> input;
    Datagen dge(0, 100);

    // profiler
    SimpleProfiler prof(Resolution::NSEC); 

    const int testIter = 50;
    const int vectLen = 10000;

    for (int i = 0; i < testIter; i++, input.clear())
    {
        for (int i = 0; i < vectLen; i++)
        {
            input.push_back(dge.getRandom());
        }

        sort(input.begin(), input.end());

        // for (int i = 0; i < input.size(); i++)
        // {
        //     cout << input[i] << ",";
        // }
        // cout << endl;



        // lets see how many times we get seven in 100 tries

        cout << "*** Test id : " << i << "  ***" << endl;

        prof.startTimeProf();
        // bool retVal = binarySearchRecursive(input,0, input.size(), 7);
        bool retVal = binarySearch(input, 7);
        prof.endTimeProf();
        prof.printRunningTime();

        if (retVal)
        {
            cout << "got 7" << endl;
        }
        else
        {
            cout << "did not get 7" << endl;
        }
    }
}