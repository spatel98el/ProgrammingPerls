// Problem statement
// displays a 16 bit positive integer in five seven segment digits
// output is an array of five byte
//  - bit i of byte j is 1 if and only if the ith segment of digit j should be on

// LED inerface class
// create LED segment display, initialized it all off
// functions
//  - display(int digit)
//  - clear()

#include <iostream>
#include <bitset>

#include <SegmentLED.hpp>
#include <LEDDisplay.hpp>

using namespace std;


int main() {

    SegmentLED led;

    for(int i = 0; i <= 3; i++) {
        LEDBitMap bm = led.display(i);
        cout << "led bm for " << i << " : " <<  std::bitset<8>(static_cast<uint8_t>(bm)) << endl;
    }


    LEDDisplay display(5); //five segment display
    display.displayNum(123);
    display.getLEDBitMaps();
    
    return 0;
}

