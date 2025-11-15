// Implement generic bitmap to track indexes

#include <iostream>

using namespace std;

class Bitmap {
    public:
    Bitmap(int bitMapSz) {
        cout << "Creating bitmap of size " << bitMapSz << endl;

        int bytes = bitMapSz/8 + (bitMapSz % 8 ? 1 : 0); //should we align ?
        bitMap = new int[bytes] {0};
    };
    ~Bitmap() {
        delete [] bitMap;
        bitMap = nullptr;
    }

    void setBitPosition(int position)
    {
        // set index of the bit position
        // set some fixed offsets
        // byte offset = number / 8
        // bit offset = number % 8
        int byOff = position / 8;
        int biOff = position % 8;

        bitMap[byOff] |= 1 << biOff;
    }
    bool getBitValue(int position) {
        return ((bitMap[position/8] & (0x1 << position%8)) != 0);
    }

    private:
    // bitmap storage
    int *bitMap;
};