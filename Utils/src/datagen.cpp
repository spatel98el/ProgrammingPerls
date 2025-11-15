// Generate unique random samples

#include <iostream>
#include <fstream>
#include <random>
#include <vector>

#include <Bitmap.hpp>

using namespace std;

int main() {
    ofstream ofile("data.txt");
    int maxRange = 0;
    // take the input for size of dataset
    cout << "Enter number of entried to be generated"<< endl;
    cin >> maxRange;
    cout << "Genreate " << maxRange << " unique entries!" << endl;


    // generate random numbers from 0 to maxRange
    default_random_engine dre;
    uniform_int_distribution did(0, maxRange);

    //use bitmap to track generation through bit maps
    auto bm = new Bitmap(maxRange);

    // generate unique 10000 ints
    int counter = 0;
    while (counter < maxRange) {
        int val = did(dre);
        if(!bm->getBitValue(val)) {
            // valid 
            bm->setBitPosition(val);
            ofile << val << endl;

            counter++;
        }
    }

    ofile.close();
}