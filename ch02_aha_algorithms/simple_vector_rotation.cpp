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

int main() {

    vector<int> input{};
    for(int i = 0; i < 100; i++)
        input.push_back(i);
        
    SimpleProfiler prof(Resolution::NSEC);

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

    cout << "Optimized reverse:" << endl;
    vector<int> test {};

    for(int i = 0; i < 100; i++)
        test.push_back(i);
    PRINTVEC(test);
    prof.startTimeProf();

    reverseOpt(test, 0, 3);
    reverseOpt(test, 4, test.size()-1);
    reverseOpt(test, 0, test.size()-1);

    prof.endTimeProf();
    prof.printRunningTime();
    
    cout << "Rotated:" << endl;
    PRINTVEC(test);

}