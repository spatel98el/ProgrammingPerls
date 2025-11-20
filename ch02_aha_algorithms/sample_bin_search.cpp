// This is not the part of the book but warm up 

// generate simple vector of random data, sort and search 

#include <vector>
#include <algorithm>
#include <iostream>

#include <Datagen.hpp>

using namespace std;

bool binarySearch(vector<int> container, int value) {
    int low = 0, high = container.size(), mid = 0;
    while(low < high) {
        mid = (high - low)/2;

        if(container[mid] == value) {
            return true;
        }
        else if(container[mid] < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
     }

     return false;
}

int main() {

    // fill temp data
    vector<int> input;
    Datagen dge(0, 100);

    for(int i = 0; i < 10; i++) {
        input.push_back(dge.getRandom());
    }

    sort(input.begin(), input.end());

    for (int i = 0; i < 10; i++) {
        cout << input[i] << endl;
    }

    // lets see how many times we get seven in 100 tries
    if (binarySearch(input, 7)) {
        cout << "got 7" << endl;
    } else {
        cout << "did not get 7" << endl;
    }
    
    
}