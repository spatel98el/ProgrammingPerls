// Generate unique random samples
// TODO
// Convert to datagen class 

#include <iostream>
#include <fstream>
#include <vector>

#include <Bitmap.hpp>
#include <Datagen.hpp>

using namespace std;

int main() {
    ofstream ofile("data.txt");
    int maxRange = 0;
    // take the input for size of dataset
    cout << "Enter number of entried to be generated"<< endl;
    cin >> maxRange;
    cout << "Genreate " << maxRange << " entries!" << endl;


    // datagen engiene to generate numbers
    Datagen dge(0, maxRange);

    //use bitmap to track generation through bit maps
    auto bm = new Bitmap(maxRange);

    // generate unique 10000 ints
    int counter = 0;
    int dupCount = 0;
    while (counter < maxRange) {
        int val = dge.getRandom();
        if(!bm->getBitValue(val)) {
            // valid 
            bm->setBitPosition(val);
            ofile << val << endl;

            counter++;
        } else {
            dupCount++;
        }
    }

    cout << "total " << counter << " elements generated. " << endl;
    cout << "total duplicate " << dupCount << " elements ignored. " << endl;

    ofile.close();
}