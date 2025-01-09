#include "PerformanceTester.h"

double PerformanceTester::testFuncPerf(void (*func)()) {
  this->t1 = high_resolution_clock::now();
  func();
  this->t2 = high_resolution_clock::now();
  delta_time = t2 - t1;
  return delta_time.count();
}

double PerformanceTester::testFuncMeanPerf(void (*func)(), int n) { return 1; }