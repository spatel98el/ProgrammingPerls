// Problem statement
// Input :      File on the disc contains 10 million records, each with max 7 digits.
// Output :     Output file with all numbers sorted in increasing order
// Constraint : Maximum 1 mb (later corrected in the text, initially this was 8m bytes) of free
//              memory available

#include <iostream>
#include <memory>
#include <fstream>
#include <vector>

using namespace std;

void setBitPosition(int position, int *bitMap) {
    // set index of the bit position
    // set some fixed offsets
    // byte offset = number / 8
    // bit offset = number % 8
    int byOff = position / 8;
    int biOff = position % 8;

    bitMap[byOff] |= 1 << biOff;
}

bool getBitValue(int position, const int * const bitMap) {
    return ((bitMap[position/8] & (0x1 << position%8)) != 0);
}

int main() {
    
    cout << "main_sort_10m" << endl;

    // allocate required bit storage
    const int maxDataLen = 10000; //start with 10k
    constexpr auto arrayLen = (maxDataLen/8) + (maxDataLen%8) + 8; // len + spare 8 bits!    
    int bitMap[arrayLen] = {0};


    //check couple of valid bit positions
    cout << getBitValue(0, bitMap) << "," << getBitValue(1000 , bitMap) << "," << getBitValue(9999, bitMap) << endl;

    // Read file containing intergers as string
    ifstream datafile("./data/data_10k.txt");

    // go through all the bits and write back corresponding output to file
    // also track dups
    int counter = 0;
    for(int val; datafile >> val;) {
        if(getBitValue(val, bitMap)) {
            counter++;
        } else {
            setBitPosition(val, bitMap);
        }
    }
    datafile.close();

    //check couple of bit positions
    cout << getBitValue(86, bitMap) << "," << getBitValue(7705, bitMap) << "," << getBitValue(3097, bitMap) << endl;

    // sequentially iterate bit positions if bit it set write back position to the file
    ofstream ofile("./data/sorted_data.txt");
    for(int pos = 0; pos < maxDataLen; pos++) {
        if(getBitValue(pos, bitMap))
            ofile << pos << endl;
    }
    ofile.close();

    cout << "number of dups : " << counter << endl;
}