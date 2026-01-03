// Problem statement:

// Rotation of i elements from tail of vector ot head
// e.g. {1 2 3 4 5} -> rotate(2)->{3 4 5 1 2}
// use temporary space of 1 to i elements

// Method:
// partition array a to a'b' which to be rotated to b'a'
// a'b' -> reverse -> ra'rb' -> reverse whole array -> r(ra'rb')

#include <iostream>
#include <vector>
#include <stack>

#include <Misc.hpp>
#include <SimpleProfiler.hpp>

using namespace std;

bool reverse(vector<int> &a, int start,  int end) {
    if (end > a.size() || start < 0) {
        cout << "out of range : " << start << "," << end << endl;
        return false;
    }
    // reverse start to end portion
    // fist with stack

    SimpleProfiler prof(Resolution::NSEC);
    prof.startTimeProf();

    stack<int> temp;

    for(auto i = a.begin() + start;  i != (a.begin() + end); i++) {
        temp.push(*i);
    }
    
    for(auto i = a.begin() + start;  i != (a.begin() + end); i++) {
        *i = temp.top();
        temp.pop();
    }

    prof.endTimeProf();
    // prof.printRunningTime();

    return true;
}

void swap(int &a, int &b) {
    if (a == b)
        return;
    int t = a;
    a = b;
    b = t;
}
bool reverseOpt(vector<int> &a, int start, int end) {
    if (start < 0 or end > a.size()) {
        cout << "out of range : " << start << "," << end << endl;
        return false;
    }

    SimpleProfiler prof(Resolution::NSEC);
    prof.startTimeProf();
    // pick up the center of the range and flip around
    int range = end - start;
    // PRINT3PARAMS(start, end, range);
    for (int i = 0; i <= range/2 ; i++) {
        swap(a[start+i], a[end-i]);// 0-3, 1-2, 
        // PRINT2PARAMS(start+i, end-i);
    }
    prof.endTimeProf();
    // prof.printRunningTime();
    // PRINTVEC(a);
    return true;
}

bool reverseJuggling(vector<int> &a, int rot) {

    if(a.size() <= rot) {
        return false;
    }
    // this is lsl op
    // from 0-n -> 0-i:i+1-n ->i+1-n:0-1
    // use one temp location
    int n = a.size();
    for(int j=0,t=0,k=0; j < rot;j++) {
        t = a[j];
        for(k=j; k + rot < n; k += rot) {
            a[k] = a[k+rot];
        }
        // k <= n , k + rot > n
        a[n- (rot - j)] = t;
    }

    // case 1 :
    // n = 9, rot = 3
    // j : 0 -> k -> {0, 3, 6} -> a[6] = a[0]
    // j : 1 -> k {1, 4} -> a[7] = a[1]
    // ..

    // case 2:
    // n = 10, rot = 3
    // j : 0 -> k {0, 3, 6} -> a[7] = a[0]
    // j : 1 -> k {1, 4} -> a[8] = a[1]

    return true;
}

int main() {
    SimpleProfiler prof(Resolution::NSEC);

    {
        vector<int> input{};
        for (int i = 0; i < 100; i++)
            input.push_back(i);

        cout << "Original:" << endl;
        PRINTVEC(input);

        prof.startTimeProf();
        reverse(input, 0, 9);
        reverse(input, 9, input.size());
        reverse(input, 0, input.size());
        prof.endTimeProf();
        prof.printRunningTime();

        cout << "Rotated:" << endl;
        PRINTVEC(input);
    }

    {
        cout << "Optimized reverse:" << endl;
        vector<int> test{};

        for (int i = 0; i < 100; i++)
            test.push_back(i);
        PRINTVEC(test);
        prof.startTimeProf();

        reverseOpt(test, 0, 3);
        reverseOpt(test, 4, test.size() - 1);
        reverseOpt(test, 0, test.size() - 1);

        prof.endTimeProf();
        prof.printRunningTime();

        cout << "Rotated:" << endl;
        PRINTVEC(test);
    }
    {
        cout << "Juggling reverse - Not working:" << endl;
        vector<int> test{};

        for (int i = 0; i < 10; i++)
            test.push_back(i);
        PRINTVEC(test);
        prof.startTimeProf();

        reverseJuggling(test, 3);

        prof.endTimeProf();
        prof.printRunningTime();

        cout << "Rotated:" << endl;
        PRINTVEC(test);
    }

    {
        // abc->cba
        cout << "Reverse 3 segments , problem 5" << endl;
                vector<int> test{};

        for (int i = 0; i < 10; i++)
            test.push_back(i);
        PRINTVEC(test);

        reverseOpt(test, 0, 3); //ar

        reverseOpt(test, 4, 6);//br
        reverseOpt(test, 7, 9);//cr

        reverseOpt(test, 4, 9); //brcrr -> cb
        reverseOpt(test, 4, 9); // cb -> cbr

        reverseOpt(test, 0, 9); //(ar(cbr))r

        PRINTVEC(test);
    }
}