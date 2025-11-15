// simple profiler to profile time point
#include <chrono>

class SimpleProfiler
{
public:
    SimpleProfiler() {
        // select preferences , clock type. precision etc
    };
    ~SimpleProfiler() {

    };
    bool Start() {
        // start profiling
    };
    bool End()
    {
        // End profiling
    }
    void RunningTime()
    {
        // end - start
    }

private:
    // start time point

    // end time point
}