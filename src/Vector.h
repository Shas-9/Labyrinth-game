#ifndef VECTOR_INCLUDE
#define VECTOR_INCLUDE

#include <iostream>

using std::cout;
using std::endl;

class Vector {
private:
  double x;
  double y;

public:
  Vector();
  Vector(double x, double y);
  Vector(int x, int y);
  void moveHorizontal(double value);
  void moveVertical(double value);

  double getX();
  double getY();

  void set(double x, double y);
  void set(int x, int y);

  void print();
};

#endif