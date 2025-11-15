// test generic bitmap to track indexes
#include <Bitmap.hpp>

using namespace std;

int main() {
    //test class

    auto newBitmap = new Bitmap(100);

    // check random places if zero initialized
    cout << newBitmap->getBitValue(0) << ","
         << newBitmap->getBitValue(49) << ","
         << newBitmap->getBitValue(99) << endl;

    newBitmap->setBitPosition(0);
    newBitmap->setBitPosition(49);
    newBitmap->setBitPosition(99);

    cout << newBitmap->getBitValue(0) << ","
         << newBitmap->getBitValue(49) << ","
         << newBitmap->getBitValue(99) << endl;
}