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
// Horizontal movement
void Vector::moveHorizontal(double value) { this->x += value; }

// Vertical movement
void Vector::moveVertical(double value) { this->y += value; }

// Getters
double Vector::getX() { return this->x; }
double Vector::getY() { return this->y; }

// Setter with double values
void Vector::set(double x, double y) {
  this->x = x;
  this->y = y;
}

// Setter with int values
void Vector::set(int x, int y) {
  this->x = x;
  this->y = y;
}