#include "Vector.h"

#include <iostream>
#include <cmath>

Vector::Vector(): x(0), y(0) {}
Vector::Vector(sf::Vector2f v): x(v.x), y(v.y) {};
Vector::Vector(double x, double y): x(x), y(y) {}
Vector::Vector(float x, float y): x(x), y(y) {}
Vector::Vector(int x, int y): x(x), y(y) {}
Vector::Vector(unsigned int x, unsigned int y): x(x), y(y) {}

double Vector::getX() const { return this->x; }
double Vector::getY() const { return this->y; }

void Vector::set(double x, double y) {
  this->x = x;
  this->y = y;
}

void Vector::set(int x, int y) {
  this->x = x;
  this->y = y;
}

double Vector::getLength() const { return sqrt(pow(this->getX(), 2) + pow(this->getY(), 2)); }

void Vector::normalize() {
  double len = this->getLength();
  this->x = x/len;
  this->y = y/len;
}

void Vector::print() const { std::cout << "{" << this->getX() << ", " << this->getY() << "}" << std::endl; }

Vector Vector::getMid(const Vector& vec1, const Vector& vec2, double delay) {
  return Vector(vec1.x - (vec1.x-vec2.x)/delay, vec1.y - (vec1.y-vec2.y)/delay);
}

Vector Vector::getMid(const Vector& vec1, const Vector& vec2) {
  return Vector::getMid(vec1, vec2, 2);
}

Vector Vector::operator+(const Vector& vec) const {
  Vector res(this->x + vec.x, this->y + vec.y);
  return res;
}

Vector& Vector::operator+=(const Vector& vec) {
  this->x += vec.x;
  this->y += vec.y;
  return *this;
}

Vector Vector::operator-(const Vector& vec) const {
  Vector res(this->x - vec.x, this->y - vec.y);
  return res;
}

Vector& Vector::operator-=(const Vector& vec) {
  this->x -= vec.x;
  this->y -= vec.y;
  return *this;
}

Vector Vector::operator*(const double d) const {
  Vector res(this->x * d, this->y * d);
  return res;
}

Vector& Vector::operator*=(const double d) {
  this->x *= d;
  this->y *= d;
  return *this;
}

Vector Vector::operator/(const double d) const {
  Vector res(this->x / d, this->y / d);
  return res;
}

Vector& Vector::operator/=(const double d) {
  this->x /= d;
  this->y /= d;
  return *this;
}

bool Vector::operator==(const Vector& vec) const {
  return this->x == vec.x && this->y == vec.y;
}
