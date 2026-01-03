#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (a > b ? a : b)

int maxSum(int *v, int n) {
    int max = 0;
    for(int i = 0; i < n; i++) {
        int sum = 0;
        for(int j = i; j < n; j++) {
            sum += v[j];
            max = MAX(max, sum);
        }
    }
    return max;
}


int maxSum2(int *v, int n) {
    // compute cumulative sum at each index
    // iterate over but get sum at idx j by
    //  cumsum[j] - cumsum[i-1]
    //  track max

    int *cumsum = (int *)malloc((n+1) * sizeof(v[0]));
    cumsum[0] = 0;
    for(int i=1; i <= n; i++) {
        cumsum[i] = cumsum[i - 1] + v[i-1];
    }
    
    // tc1: cumsum {1,3,6,10,15,21}
    // i = 0: 0, 2, 5, 9, 14, 20* 
    // i = 1: 0, 4, 8, 13, 19
    // i = 2: 

    int max = 0;
    for(int i = 0 ; i <= n; i++) {
        for(int j = i+1; j <= n; j++) {
            max = MAX(max, (cumsum[j] - cumsum[i]));
        }
    }
    free(cumsum);
    return max;
}

int  maxSumDC(int *v, int l, int u) {
    if(l > u) {
        return 0;
    }

    if(l == u) {
        return v[l];
    }

    int m = (l + u)/2;
    // get max sum for left and right sub array
    int lmax = 0, sum = 0; 
    for(int i = m; i >= l; i--) {
        sum += v[i];
        lmax = MAX(lmax, sum);
    }
    // track sum of right subhalf
    int rmax = 0;
    sum = 0; 
    for(int i = m+1; i <=u; i++) {
        sum += v[i];
        rmax = MAX(rmax, sum);
    }
    
    return MAX(lmax + rmax, MAX(maxSumDC(v, l, m), maxSumDC(v, m+1, u)));
}

int maxSum3(int *v, int n) {
    return(maxSumDC(v, 0, n-1));
}

// Implement J Kadane's algo
// mysterious how actually you can come up with this
int maxSum4(int *v, int n) {
    // track global max
    // track +ve max sofar - why only positive max ? because -ve occurance will reduce sum
    //  - this means we are resetting it on 0
    //  - if we don't reset on zero it will track -ve as well ?
    // TODO how to extend this for 3 sum or nsum ?
    int maxSoFar = 0,maxGlobal = 0;
    for(int i = 0; i < n; i++) {
        maxSoFar = MAX(maxSoFar + v[i], 0); //tracks non zero sum
        maxGlobal = MAX(maxGlobal, maxSoFar); // track global max
    }
    return maxGlobal;
}

void main() {

    // test 1
    int tc1[] = {1,2,3,4,5,6}; //ans: 21
    int tc2[] = {-1,-2,-3,-4,-5,-6}; // ans: 0
    int tc3[] = {1,2,-3,4,5,-6}; // ans: 9
    int tc4[] = {1,-2,-3,-4,-5,-6}; // ans: 1
    
    printf("maxsum\n");
    printf("tc1:%d\n", maxSum(tc1, 6));
    printf("tc2:%d\n", maxSum(tc2, 6));
    printf("tc3:%d\n", maxSum(tc3, 6));
    printf("tc4:%d\n", maxSum(tc4, 6));
    
    printf("maxsum2\n");
    printf("tc1:%d\n", maxSum2(tc1, 6));
    printf("tc2:%d\n", maxSum2(tc2, 6));
    printf("tc3:%d\n", maxSum2(tc3, 6));
    printf("tc4:%d\n", maxSum2(tc4, 6));

    printf("maxsum3 (DC)\n");
    printf("tc1:%d\n", maxSum3(tc1, 6));
    printf("tc2:%d\n", maxSum3(tc2, 6));
    printf("tc3:%d\n", maxSum3(tc3, 6));
    printf("tc4:%d\n", maxSum3(tc4, 6));

    printf("maxsum4 (J Kadane)\n");
    printf("tc1:%d\n", maxSum4(tc1, 6));
    printf("tc2:%d\n", maxSum4(tc2, 6));
    printf("tc3:%d\n", maxSum4(tc3, 6));
    printf("tc4:%d\n", maxSum4(tc4, 6));
}
