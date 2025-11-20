#include <SimpleProfiler.hpp>

using namespace std;

int main() {
    SimpleProfiler prof;

    prof.startTimeProf();

    cout << "Hello world!" << endl;

    prof.endTimeProf();

    prof.printRunningTime();

    return 0;

}