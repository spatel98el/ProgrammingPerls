// variation of bin search to find first occurance

#include <stdio.h>

int binSearchLO(int *a, int n, int key){ // a, n = 11, keys = 2
    int l = 0, h = n-1, m;
    int lo = -1; 

    while(l <= h) { 
        m = (l + h)/2;//{0, 10, 5};{0, 4, 2}; {3,4,3};{4,4,4} ; {4, 3, break}
        if(key == a[m]) { 
            l = m + 1;
            lo = m; // 5
        } else if(key > a[m]) {
            l = m + 1;
        } else { // key < a[m]
            h = m - 1;
        }
    }
    return lo;
}
int binSearchFO(int *a, int n, int key){ // a, n = 11, keys = 2
    int l = 0, h = n-1, m;
    int fo = -1; 

    while(l <= h) { 
        m = (l + h)/2;//{0, 10, 5};{0, 4, 2}; {3,4,3};{4,4,4} ; {4, 3, break}
        if(key == a[m]) { 
            h = m - 1;
            fo = m; // 5
        } else if(key > a[m]) {
            l = m + 1;
        } else { // key < a[m]
            h = m - 1;
        }
    }
    return fo;
}

int binSearch(int *a, int n, int key){ // a, n = 11, keys = 2
    int l = 0, h = n-1, m;
    int lo = -1; 

    while(l <= h) { 
        m = (l + h)/2;//{0, 10, 5};{0, 4, 2}; {3,4,3};{4,4,4} ; {4, 3, break}
        if(key == a[m]) { 
            return m; // 5
        } else if(key > a[m]) {
            l = m + 1;
        } else { // key < a[m]
            h = m - 1;
        }
    }
    return -1;
}
void binSearchRecurse(int *a, int l, int h, int key, int *res) {
    if(l < h && *res != -1)
        return;

    int m = (l+h)/2;

    if(key == a[m]){
        *res = m;
        return;
    } else if(key > a[m]){
        binSearchRecurse(a, m+1, h, key, res);
    } else {
        binSearchRecurse(a, l, m-1, key, res);
    }
}
int main() {

    int a[] = {1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,4,5};
    int n = sizeof(a)/sizeof(a[0]);

    int fo = binSearchFO(a, n, 3); 
    int lo = binSearchLO(a, n, 3); 

    printf("FO : %d, LO : %d \n", fo , lo);

    int res = -1;
    binSearchRecurse(a, 0, n-1, 3, &res);
    if(res != -1) {
        printf("binSearchRecurse : key at loc %d\n", res);
    } else {
        printf("binSearchRecurse : unable to find key!\n");
    }
    
    if(binSearch(a, n, 3) != -1) {
        printf("binSearch: key at loc %d\n", res);
    } else {
        printf("binSearch: unable to find key!\n");
    }
}
