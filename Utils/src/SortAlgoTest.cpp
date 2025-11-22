#include <iostream>
#include <string>
#include <algorithm>

#include <SortAlgos.hpp>
#include <SimpleProfiler.hpp>
#include <Misc.hpp>

using namespace std;

int main() {

    
    string s{};

    PRINT1PARAM("Enter string:");
    cin >> s;

    SortAlgos sa;

    SimpleProfiler prof(Resolution::NSEC);
    prof.startTimeProf();

    string ss = sa.alphabeticalSort(s);

    prof.endTimeProf();
    PRINT2PARAMS("My algoSort:", ss);
    prof.printRunningTime();



    // system sort
    prof.startTimeProf();
    sort(s.begin(), s.end());
    prof.endTimeProf();
    PRINT2PARAMS("System sort : ", s);
    prof.printRunningTime();

}