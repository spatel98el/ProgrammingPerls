// problem 11 of ch8 of PP by JB
#include <stdio.h>
#include <stdlib.h>


int *cumSumCost(int *costs, int n) {
    int *cumsum = (int *)calloc(n, sizeof(int));
    
    cumsum[0] = costs[0];
    for(int i = 1; i < n; i++) {
        cumsum[i] = costs[i] + cumsum[i-1];
    }
    return cumsum;
}
// a & b [0, n-1]
int getCost(int *cumsum, int a, int b) {
    if(a == b) {
        return 0;
    }

    if(a == 0) {
        return cumsum[b];
    } else {
        return (cumsum[b] - cumsum[a-1]);
    }
}

void main() {
    int costs[] = {0,3,6,1,6};
    int *cumsum = cumSumCost(costs, 5);
    // cumsum - [0,3,9,10,16]
    // 0-4, -> 18
    // 4,4 -> 0
    // 1,3 -> 16

    printf("cost %d-%d = %d\n", 0, 4, getCost(cumsum, 0, 4));
    printf("cost %d-%d = %d\n", 4, 4, getCost(cumsum, 4, 4));
    printf("cost %d-%d = %d\n", 1, 3, getCost(cumsum, 1, 3));
}
