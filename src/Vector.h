#ifndef VECTOR_INCLUDE
#define VECTOR_INCLUDE

#include <iostream>

using std::cout;
using std::endl;

struct Vector {
  double x;
  double y;
  
  Vector();
  Vector(double x, double y);
  Vector(int x, int y);

  void print();
};

#endif