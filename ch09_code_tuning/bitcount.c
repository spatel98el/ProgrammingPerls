// give a long sequence of bytes , count total number of 1 bits
// input:   char array, and length
// output:  total num of ones in the array
// algo:    scan all bytes , examin bits and update counter -> n bytes * 8 -> o(8n), space o(n)
// variations:  bit sequences, zeros and one, transitions, rlc packing
#include <stdio.h>
#include <time.h>

#define BITS_IN_BYTE 8
int countBits(char *in, int n) {
    struct timespec start, end;
    double tElapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int count = 0;

    for(int i =0; i < n; i++) {
        for(int j=0; j < BITS_IN_BYTE; j++) {
            if(in[i] & (0x01 << j)) {
                count++;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("elapsed time(nsec) : %ld\n", ((end.tv_nsec - start.tv_nsec)));

    return count;
}
// num bits in 0-f
unsigned char LUT[] = 
                    {0, 1, 1, 2, 1, 2, 2, 3, /*0-7*/
                     1, 2, 2, 3, 2, 3, 3, 4 }; /*8-15*/

int countBitsOpt1(char *in, int n) {
    struct timespec start, end;
    double tElapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int count = 0;
    // extract each nibble and count bits
    for(int i = 0; i < n; i++) {
        count += LUT[(in[i] & 0x0f)]; // lower nibble
        count += LUT[(in[i] & 0xf0) >> 4]; // upper nibble
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("elapsed time(nsec) : %ld\n", ((end.tv_nsec - start.tv_nsec)));
    return count;
}

int countTransitions(char *in, int n) {
    // track bits, count transition, maintain state to skip
    int count = 0;
    int state = 0;//first LS bit


    for(int i = 0; i < n; i++) {
        for(int j=0; j < BITS_IN_BYTE; j++) {
            if(((in[i] & (0x1 << j))) && state == 0) {
                count++;
                state = 1;
            } else if(((in[i] & (0x1 << j)) == 0x0) && state == 1) {
                count++;
                state = 0;
            }
        }        
    }

    return count;
}

void testBitTransitions() {
    printf("Bit transition count scaffold\n");
    char tc1[] = {0x00, 0x00, 0x00, 0x00};
    char tc2[] = {0xff, 0xff, 0xff, 0xff};
    char tc3[] = {0x81, 0x81, 0x81, 0x81};// 10000001100000011000000110000001 -> 9
    char tc4[] = {0x99, 0x99, 0x99, 0x99};

    printf("Basic version:\n");
    printf("tc1 bits:%d\n", countTransitions(tc1, 4));
    printf("tc2 bits:%d\n", countTransitions(tc2, 4));
    printf("tc3 bits:%d\n", countTransitions(tc3, 4));
    printf("tc4 bits:%d\n", countTransitions(tc4, 4));// 10011001 10011001 10011001 10011001
}
void testBitCount() {
    printf("Bit count scaffold\n");
    char tc1[] = {0x00, 0x00, 0x00, 0x00};
    char tc2[] = {0xff, 0xff, 0xff, 0xff};
    char tc3[] = {0x81, 0x81, 0x81, 0x81};// 10000001100000011000000110000001 -> 9
    char tc4[] = {0x99, 0x99, 0x99, 0x99};// 10011001 10011001 10011001 10011001 -> c=3

    printf("Basic version:\n");
    printf("tc1 bits:%d\n", countBits(tc1, 4));
    printf("tc2 bits:%d\n", countBits(tc2, 4));
    printf("tc3 bits:%d\n", countBits(tc3, 4));
    printf("tc4 bits:%d\n", countBits(tc4, 4));

    printf("optimized version:\n");
    printf("tc1 bits:%d\n", countBitsOpt1(tc1, 4));
    printf("tc2 bits:%d\n", countBitsOpt1(tc2, 4));
    printf("tc3 bits:%d\n", countBitsOpt1(tc3, 4));
    printf("tc4 bits:%d\n", countBitsOpt1(tc4, 4));
}

void main() {
//    testBitCount();
    testBitTransitions();
}
