#ifndef VECTOR_INCLUDE
#define VECTOR_INCLUDE

#include <iostream>

using std::cout;
using std::endl;

class Vector {
private:

public:
  double x;
  double y;
  
  Vector();
  Vector(double x, double y);
  Vector(int x, int y);
  Vector(unsigned int x, unsigned int y);
  void moveHorizontal(double value);
  void moveVertical(double value);

  double getX();
  double getY();

  void set(double x, double y);
  void set(int x, int y);

  static Vector subtract(Vector vec1, Vector vec2);
  double getLength();
  void multiply(double len);
  void normalize();

  void print();

  static Vector getMid(Vector vec1, Vector vec2, double delay);
  static Vector getMid(Vector vec1, Vector vec2);

  Vector operator+(const Vector& vec);
  Vector& operator+=(const Vector& vec);
  Vector operator-(const Vector& vec);
  Vector& operator-=(const Vector& vec);
  Vector operator*(const double d);
  Vector& operator*=(const double d);
  Vector operator/(const double d);
  Vector& operator/=(const double d);
  bool operator==(const Vector& vec);
};

#endif