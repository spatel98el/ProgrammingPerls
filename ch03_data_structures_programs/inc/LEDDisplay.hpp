#ifndef _LEDDISPLAY_HPP
#define _LEDDISPLAY_HPP

// this class reptesents 5 LED display
#include <iostream>
#include <vector>

#include <SegmentLED.hpp>

namespace std {
    class LEDDisplay {
        public:
            // pass number of LED segments to create
            LEDDisplay(unsigned int numSegments) : m_numSegments(numSegments) {
                // create segments
                display.resize(numSegments);
                for(auto led : display) {
                    led.clear();
                }
            };

            ~LEDDisplay() {
                clearDisplay();
            };

            bool displayNum(unsigned int value) {
                // get each digit and send for display
                int ledIndex = 0;
                int digit = 0;

                while(ledIndex < m_numSegments) {

                    digit = 0;                    
                    if(value > 0) {
                        digit = value % 10;
                        value /= 10;
                    }

                    cout << "Display digit :" << digit << endl;
                    // display
                    display[ledIndex++].display(digit);
                }

                return true;
            };

            void getLEDBitMaps() {
                for(int i =0 ; i < m_numSegments; i++) {
                    auto bm = display[i].getBitmap();
                    cout << "LED:" << i << ", bitmap:" << std::bitset<8>(static_cast<uint8_t>(bm)) << endl;
                }
            }

            void clearDisplay() {
                for(auto led : display) {
                    led.clear();
                }
            }

        private:
            vector<SegmentLED> display;
            unsigned int m_numSegments;
    };
};

#endif //_LEDDISPLAY_HPP