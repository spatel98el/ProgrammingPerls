// Test data generator
#include <iostream>

#include <Datagen.hpp>

using namespace std;

int main() {

    Datagen dge(100, 200);

    for (int i = 0; i < 25; i++) {
        cout << dge.getRandom() << endl;
    }

    return 0;
}