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

void Vector::moveVertical(double value) { this->x += value; }
void Vector::moveHorizontal(double value) { this->y += value; }

double Vector::getXPosition() { return this->x; }
double Vector::getYPosition() { return this->y; }

void Vector::setPosition(double x, double y) {
  this->x = x;
  this->y = y;
}

void Vector::setPosition(int x, int y) {
  this->x = x;
  this->y = y;
}