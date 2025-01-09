#ifndef PERFORMANCE_TESTER_INCLUDE
#define PERFORMANCE_TESTER_INCLUDE

#include "misc.h"

#include <fstream>
#include <iostream>
#include <string>

#include <chrono>
using namespace std::chrono_literals;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::seconds;
using std::chrono::time_point;


template <typename INDEP_VAR_TYPE = double>
class PerformanceTester {
protected:
  time_point<high_resolution_clock> t1;
  time_point<high_resolution_clock> t2;
  duration<double> delta_time;
public:
  double testFuncPerf(void (*func)()) {
    this->t1 = high_resolution_clock::now();
    func();
    this->t2 = high_resolution_clock::now();
    delta_time = t2 - t1;
    return delta_time.count();
  }
  double testFuncMeanPerf(void (*func)(), int n) {
    double total_time = 0;
    for (int i = 0; i < n; i++) total_time += this->testFuncPerf(func);
    return total_time/n;
  }
  double testVariableFuncPerf(void (*func)(INDEP_VAR_TYPE), INDEP_VAR_TYPE var) {
    this->t1 = high_resolution_clock::now();
    func(var);
    this->t2 = high_resolution_clock::now();
    delta_time = t2 - t1;
    return delta_time.count();
  }
  double testVariableFuncMeanPerf(void (*func)(INDEP_VAR_TYPE), INDEP_VAR_TYPE var, int n) {
    double total_time = 0;
    for (int i = 0; i < n; i++) total_time += this->testVariableFuncPerf(func, var);
    return total_time/n;
  }
  void plotFuncPerf(std::string independent_var, void (*func)(INDEP_VAR_TYPE), int n, INDEP_VAR_TYPE range_begin, INDEP_VAR_TYPE range_end, INDEP_VAR_TYPE step, bool add_step = true) {
    std::string file_location = "data.txt";
    std::ofstream MyFile(file_location);

    if (add_step) {
      for (INDEP_VAR_TYPE current = range_begin; current < range_end; current += step) {
        double time = this->testVariableFuncMeanPerf(func, current, n);
        MyFile << current << " " << time << std::endl;
      }
    } else {
      for (INDEP_VAR_TYPE current = range_begin; current < range_end; current *= step) {
        double time = this->testVariableFuncMeanPerf(func, current, n);
        MyFile << current << " " << time << std::endl;
      }
    }

    MyFile.close();

    std::string cmd = "graph -T png -W 0.004 --bitmap-size 1500x1500 -F HersheySans-Bold -f 0.04 -g 4 -X \"" + independent_var + "\" -Y \"" + "time (seconds)\" " + file_location + " > " + file_location + ".png";
    std::cout << cmd << std::endl;
    exec(cmd.c_str());
  }
};

#endif