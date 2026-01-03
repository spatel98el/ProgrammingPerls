// understand stdlib function qsort

#include <stdlib.h>
#include <stdio.h>

int comp (const void *d1, const void *d2) {
    int l = *((int *)d1), r = *((int *)d2);
    if(l < r)
        return -1;
    else if(l > r)
        return 1;
    else
        return 0;

}

void main() {

    int a[] = {3, 4,8,1,4,9,3,6,23,1,6,4,13,18};
    int n = sizeof(a)/sizeof(int);
    
    qsort(a, n , sizeof(int), comp);

    for(int i=0; i < n;i ++) {
        printf("%d,", a[i]);
    }
    printf("\n");

}