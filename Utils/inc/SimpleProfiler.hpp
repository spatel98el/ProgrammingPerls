// simple profiler to track and print time

// TODO:
// Multi step profiler
// output stream, could be console of file or bufffer ?
// clock selection


#include <chrono>
#include <iostream>

namespace std
{
    enum class Resolution{
        USEC = 1,
        NSEC= 2,
    };

    class SimpleProfiler
    {
    public:
        typedef chrono::system_clock::time_point timepoint;

        SimpleProfiler(Resolution res=Resolution::USEC) : res(res) {
            // select preferences , clock type. precision etc
        };
        ~SimpleProfiler() {

        };
        timepoint startTimeProf() {
            // start profiling
            start = chrono::system_clock::now();
            return start;
        };
        timepoint endTimeProf()
        {
            // End profiling
            end = chrono::system_clock::now();
            return end;
        }
        void printRunningTime()
        {
            // end - start
            if (res == Resolution :: NSEC) {
                auto diff = chrono::duration_cast<chrono::nanoseconds>(end - start);
                cout << "Running time : " << diff.count() << " nsec" << endl;
            } else {
                auto diff = chrono::duration_cast<chrono::microseconds>(end - start);
                cout << "Running time : " << diff.count() << " usec" << endl;
            }
        }

    private:
        // start time point
        timepoint start;

        // end time point
        timepoint end;

        // Resolution
        Resolution res;
    };
};