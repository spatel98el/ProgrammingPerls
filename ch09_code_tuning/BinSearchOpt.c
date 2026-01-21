// binary search optimizations

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int nearestTwoPow(unsigned int val) {
    if(val == 0 ){
        return 0;
    }
    int pos=0, lastPos=0;
    while(val) {
        if(val & 0x01) {
            lastPos = pos;
        }
        pos++;
        val >>= 1;
    }
    return(0x1 << lastPos);
}

int bsearchFixedSz(int *a, int n, int k) {
    // a[745] = k, n = 1000
    // l=488, i=512; i=256, a[744]; i=128...1, a[745] -> p=745
    // a[0] = k, n = 1000
    // l=-1, i=512; i=256...1 ->255..0
    // a[511] = k, n = 1000
    // l=-1,i=256; l=255+128=383+64=447+32=479+16=495+8=503+4=507+2=509+1=510, i=1; p=511

    struct timespec start, end;
    double tElapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    int np = nearestTwoPow(n);
    // search pointer in power of two
    int l = -1, i = np;
    // set lower bound l based on if its upper 2^n or lower 2^n
    if(k > a[np-1]) {
        // upper 512 elements
        l = n - np; //488-1k
    }
    //debug
    //printf("Before - l:%d, i:%d\n", l, i);
    // search from l to n, with moving l to right partition and search with halving i
    while(i != 1) {
        i = i/2;
        if(a[l + i] < k) { // 488 + 256 = 744 -> 745; 744 + 128 = 872; 744 + 64 = 808 ; 776; 
            // upper
            l = l + i; // 744
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("elapsed time(usec) : %lf\n", ((end.tv_nsec - start.tv_nsec)/1000.0));

    int p = l + i;
    //debug
    //printf("After - l:%d, i:%d\n", l, i);

    if(p >= n || a[p] != k) {
        return -1;
    } else {
        return p;
    }
}

int bsearchOpt1(int *a, int n, int k) {
    // [2,4,6,8,10,12] - 10
    // l=-1,u=6,m=2;
    // l=2,u=5,m=3
    // l=3,u=5,m=4 -> hit
    // 11
    // l=4,u=5 -> exit
    
    struct timespec start, end;
    double tElapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int l=-1, u=n, m;
    while(l+1 !=  u) {
        m = (l + u) /2;
        if(a[m] < k) {
            l = m;
        } else {
            u = m;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("elapsed time(usec) : %lf\n", ((end.tv_nsec - start.tv_nsec)/1000.0));

    // no equal check instead relying on u to move to exact index
    if(u == n || a[u] != k) {
        return -1;
    } else {
        return u;
    }

}

int bsearchNoOpt(int *a, int n, int k) {
    // seach over range 0-n-1, value k
    // [2,4,6,8,10,12] - 10
    // l=0,u=5,m=2;
    // l=3,u=5,m4 -> hit
    // 11
    // l=0,u=5,m=2;
    // l=3,u=5,m=4
    // l=5,u=5 -> -1
    // 1
    // l=0,u=5,m=2;
    // l=0,u=1,m=0
    // l=0,u=-1 -> break
    // 13
    // l=0,u=5,m=2;
    // l=3,u=5,m=4;
    // l=5,u=5,m=5; -> hit
    // l=6,u=5 ->
    
    struct timespec start, end;
    double tElapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int l=0, u=n-1;
    int m;
    while(l <= u) {
        m = (l+u)/2; //divisions are constly
        if(a[m] < k) {
            // upper
            l = m+1;
        } else if(a[m] > k) {
            // lower
            u = m-1;
        } else {
            clock_gettime(CLOCK_MONOTONIC, &end);
            printf("elapsed time(usec) : %lf\n", ((end.tv_nsec - start.tv_nsec)/1000.0));
            return m;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("elapsed time(usec) : %lf\n", ((end.tv_nsec - start.tv_nsec)/1000.0));
    return -1; //not found
}

#define DATA_SZ 100000

void main() {
    int *tc1 = (int *)malloc(DATA_SZ*sizeof(int));
    for(int i = 0; i < DATA_SZ; i++) {
        tc1[i] = i;
    }
#if 0
    printf("samples:\n");
    for(int i=0; i < 10; i++){
        printf("%d,", tc1[i*5]);
    }
    printf("\n");

    printf("found %d at idx : %d\n",10, bsearchNoOpt(tc1, DATA_SZ, 10034));
    printf("found %d at idx : %d\n",11, bsearchNoOpt(tc1, DATA_SZ, 11045));
    printf("found %d at idx : %d\n",1, bsearchNoOpt(tc1, DATA_SZ, 106856));
    printf("found %d at idx : %d\n",2, bsearchNoOpt(tc1, DATA_SZ, 2067));
    printf("found %d at idx : %d\n",12, bsearchNoOpt(tc1, DATA_SZ, 12476));
    printf("found %d at idx : %d\n",13, bsearchNoOpt(tc1, DATA_SZ, 99999));

    printf("opt1:\n");
    printf("found %d at idx : %d\n",10, bsearchOpt1(tc1, DATA_SZ, 10034));
    printf("found %d at idx : %d\n",11, bsearchOpt1(tc1, DATA_SZ, 11045));
    printf("found %d at idx : %d\n",1, bsearchOpt1(tc1, DATA_SZ, 106856));
    printf("found %d at idx : %d\n",2, bsearchOpt1(tc1, DATA_SZ, 2067));
    printf("found %d at idx : %d\n",12, bsearchOpt1(tc1, DATA_SZ, 12476));
    printf("found %d at idx : %d\n",13, bsearchOpt1(tc1, DATA_SZ, 99999));
#endif
    const int fixedSz = 10000;
    int k;
    int *tc2 = (int *)malloc(fixedSz * sizeof(int));
    for(int i = 0; i < fixedSz; i++) {
        tc2[i] = i*10;
    }
    tc2[0] = 8;
    tc2[9999] = 99989;
    tc2[511] = 5109;
    
    printf("opt1:\n");
    k = 8;
    printf("found %d at idx : %d\n",k, bsearchOpt1(tc2, fixedSz, k));
    k = 99989;
    printf("found %d at idx : %d\n",k, bsearchOpt1(tc2, fixedSz, k));
    k = 5109;
    printf("found %d at idx : %d\n",k, bsearchOpt1(tc2, fixedSz, k));

    printf("opt2 - fixed size:\n");
    k = 8;
    printf("found %d at idx : %d\n",k, bsearchFixedSz(tc2, fixedSz, k));
    k = 99989;
    printf("found %d at idx : %d\n",k, bsearchFixedSz(tc2, fixedSz, k));
    k = 5109;
    printf("found %d at idx : %d\n",k, bsearchFixedSz(tc2, fixedSz, k));


    printf("nearestTwoPow:\n");
    int val = 512;
    printf("nearest pow %d is 0x%x\n", val, nearestTwoPow(val));
    val=510;
    printf("nearest pow %d is 0x%x\n", val, nearestTwoPow(val));
    val=513;
    printf("nearest pow %d is 0x%x\n", val, nearestTwoPow(val));
    val=0xffff;
    printf("nearest pow %d is 0x%x\n", val, nearestTwoPow(val));

    free(tc1);
    free(tc2);

}
