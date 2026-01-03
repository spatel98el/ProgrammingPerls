// kth order linear reccurence : previous k terms to compute n
// given : 
// a1...ak  -> array of numbers
// c1..ck+1 -> array of numbers
// k & m -> indexes
// output:
// compute a1 to am

#include <stdio.h>

int computeRecurrence(int a[], const int c[], const int m, const int k) { //k = 5, m = 6
    // compute linear reccurence
    // an = sigma(ci * aj)  where i : {0..k-1}
    // m >= k
    // add last add ck+1

    // range check
    if(m < k) {
        return -1; // error case
    }
    
    int sum = 0;
    int i = 0, j = m; 
    for(; i < k ; i++){
        sum += c[i]*a[m-i-1];
    }
    sum += c[k]; // add ck+1 : i=5
    a[m] = sum;
    printf("m:%d, k:%d, sum:%d \n", m, k, sum);

    return sum;
}


int main() {
    int a[12] = {0}; //12 entries
    int c[] = {4,7,3,7,4,5,7,3,5,6,4,6,8}; // 13 entries



    int k = 2;
    int m = 6;

    for(int n = 0; n < m; n++) {
        int sum = computeRecurrence(a, c, n, k);
    }

}