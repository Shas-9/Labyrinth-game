#include "Vector.h"

Vector::Vector(double x, double y) {
  this->x = x;
  this->y = y;
}

Vector::Vector(int x, int y) {
  this->x = x;
  this->y = y;
}

Vector::Vector() {
  this->x = 0;
  this->y = 0;
}

void Vector::moveHorizontal(double value) { this->x += value; }
void Vector::moveVertical(double value) { this->y += value; }

double Vector::getX() { return this->x; }
double Vector::getY() { return this->y; }

void Vector::set(double x, double y) {
  this->x = x;
  this->y = y;
}

void Vector::set(int x, int y) {
  this->x = x;
  this->y = y;
}