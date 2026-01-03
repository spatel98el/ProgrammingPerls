// This class represent operations for defining and controlling operations for segmented LEDs
#ifndef _SEGMENTLED_H
#define _SEGMENTLED_H

namespace std {

    enum class LEDBitMap : uint8_t {
        ZERO = 0b01111101,
        ONE = 0b01010000,
        TWO = 0b00110110,
        THREE = 0b01010111,
        CLEAR = 0b00000000,
        INVALID = 0b00101111, //display E for error
    };

    class SegmentLED {
        public:
            SegmentLED(LEDBitMap v) {bitmap = v;};
            SegmentLED() {bitmap = LEDBitMap :: ZERO;};
            ~SegmentLED() {bitmap = LEDBitMap :: ZERO;};

            LEDBitMap display(unsigned int digit) {
                // check the range
                if (digit > 9) {
                    return LEDBitMap :: INVALID ;
                }

                // set bitmap to segment to be turned on
                switch(digit) {
                    case 0:
                        bitmap = LEDBitMap :: ZERO;
                        break;
                    case 1:
                        bitmap = LEDBitMap :: ONE;
                        break;
                    case 2:
                        bitmap = LEDBitMap :: TWO;
                        break;
                    case 3:
                        bitmap = LEDBitMap :: THREE;
                        break;
                    default:
                        cout << "digit " << digit << " is not supported yet!" << endl;
                        bitmap = LEDBitMap :: INVALID;
                        break;
                }

                return bitmap;
            };

            LEDBitMap getBitmap () {
                return bitmap;
            }
            void clear()
            {
                // reset bitmap
                bitmap = LEDBitMap :: CLEAR;
            };
        private:
            // segment bit map , using bits 0-6
            // Segment mapping from bits 7-0, 7 unused: |x|6|5|4|3|2|1|0|
            LEDBitMap bitmap; 
    };
};

#endif //_SEGMENTLED_H