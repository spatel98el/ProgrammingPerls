#include <iostream>
#include <fstream>
#include <random>
#include <vector>

using namespace std;

int main() {
    ofstream ofile("./data/data_10k.txt");
    const int maxRange = 10000;

    // generate random numbers from 0 to maxRange
    default_random_engine dre;
    uniform_int_distribution did(10, maxRange);

    // generate 10000 ints
    for(int i = 0; i < 10000; i++)
        ofile << did(dre) << endl;

    ofile.close();
}