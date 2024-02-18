#include "Vector.h"

// Overloaded constructor with double values
Vector::Vector(double x, double y) {
  this->x = x;
  this->y = y;
}

// Overloaded constructor with int values
Vector::Vector(int x, int y) {
  this->x = x;
  this->y = y;
}

// Default constructor
Vector::Vector() {
  this->x = 0;
  this->y = 0;
}

void Vector::print() {
  cout << "{" << this->x << ", " << this->y << "}" << endl;
}