// we want to find start and end of particular key
// search return start and end of key

#include <stdlib.h>
#include <stdio.h>

int comp(const void *d1, const void *d2) {
    int l = *((int *)d1), r = *((int *)d2);
    if(l < r)
        return -1;
    else if (l > r)
        return 1;
    else
        return 0;
}

int bsearchWithRange(int *a, int key, int n, int *rr, int *rl) {
    int l = 0, h = n, mid = (l + h)/2;

    while(l < n) {
        if(a[mid] > key){
            h = mid -1;
        } else if (a[mid] < key) {
            l = mid +1;
        } else {
            // how to find starting and end range 
            printf("found %d at of offset %d\n", key, mid);
            *rl = mid; 
            *rr = mid;
            while(a[++(*rr)] == key)
                ;
            while(a[--(*rl)] == key)
                ;
            (*rr)--; (*rl)++;
            return 1;
        }
    }

    return 0;
}

int main(int argc, char **argv) {

    int a[] = {1,4,7,3,7,4,2,8,6,3,5,7,2,5,4,2,5,7,8,4,9,1,0,3,6,4,};
    int n = sizeof(a)/sizeof(int);
    qsort(a, n, sizeof(int), comp);

    for(int i = 0; i < n; i++) {
        printf("%d,", a[i]);
    }
    printf("\n");

    int key = 8;
    int *v = bsearch(&key, a, n, sizeof(int), comp);
    if(v != NULL) {
        printf("found %d at offset %ld\n", *v, (v-a));
    } else {
        printf("unable to find value!\n");
    }

    int rr=0, rl=0;
    if(bsearchWithRange(a, 4, n, &rr, &rl)) {
        printf("rl=%d, rr=%d\n", rl, rr);
    } else {
        printf("Number not found!\n");
    }

}

