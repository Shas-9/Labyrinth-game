#ifndef PERFORMANCE_TESTER_INCLUDE
#define PERFORMANCE_TESTER_INCLUDE

#include <chrono>
using namespace std::chrono_literals;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::seconds;
using std::chrono::time_point;

// delta_time = t2 - t1;
// t2 = high_resolution_clock::now();

class PerformanceTester {
protected:
  time_point<high_resolution_clock> t1;
  time_point<high_resolution_clock> t2;
  duration<double> delta_time;
public:
  double testFuncPerf(void (*func)());
  double testFuncMeanPerf(void (*func)(), int n);
};

#endif