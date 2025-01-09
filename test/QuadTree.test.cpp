#include "../src/PerformanceTester.h"

#include <iostream>

void testFunc() {
  for (int i = 0; i < 1000; i++) {
    std::cout << i << std::endl;
  }
}

int main() {
  PerformanceTester perf;
  std::cout << perf.testFuncPerf(&testFunc) << std::endl;
}