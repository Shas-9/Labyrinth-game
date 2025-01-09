#include "PerformanceTester.h"

double PerformanceTester::testFuncPerf(void (*func)()) {
  this->t1 = high_resolution_clock::now();
  func();
  this->t2 = high_resolution_clock::now();
  delta_time = t2 - t1;
  return delta_time.count();
}

double PerformanceTester::testFuncMeanPerf(void (*func)(), int n) {
  double total_time = 0;
  for (int i = 0; i < n; i++) total_time += this->testFuncPerf(func);
  return total_time/n;
}