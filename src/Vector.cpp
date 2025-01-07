#include "Vector.h"
#include <cmath>

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

// Overloaded constructor with unsigned int values
Vector::Vector(unsigned int x, unsigned int y) {
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

Vector Vector::subtract(Vector vec1, Vector vec2) {
  return Vector(abs(vec1.getX()-vec2.getX()), abs(vec1.getY()-vec2.getY()));
}

double Vector::getLength() {
  return sqrt(pow(this->getX(), 2) + pow(this->getY(), 2));
}

void Vector::multiply(double len) {
  this->x = x*len;
  this->y = y*len;
}

void Vector::normalize() {
  double len = this->getLength();
  this->x = x/len;
  this->y = y/len;
}

void Vector::print() {
  cout << "{" << this->getX() << ", " << this->getY() << "}" << endl;
}

Vector Vector::getMid(Vector vec1, Vector vec2, double delay) {
  Vector res(-(vec1.x-vec2.x)/delay, -(vec1.y-vec2.y)/delay);
  return Vector(vec1.x+res.x, vec1.y+res.y);
}

Vector Vector::getMid(Vector vec1, Vector vec2) {
  return Vector::getMid(vec1, vec2, 2);
}

Vector Vector::operator+(const Vector& vec) {
    Vector res(this->x + vec.x, this->y + vec.y);
    return res;
}

Vector& Vector::operator+=(const Vector& vec) {
    this->x += vec.x;
    this->y += vec.y;
    return *this;
}

Vector Vector::operator-(const Vector& vec) {
    Vector res(this->x - vec.x, this->y - vec.y);
    return res;
}

Vector& Vector::operator-=(const Vector& vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
}

Vector Vector::operator*(const double d) {
    Vector res(this->x * d, this->y * d);
    return res;
}

Vector& Vector::operator*=(const double d) {
    this->x *= d;
    this->y *= d;
    return *this;
}

Vector Vector::operator/(const double d) {
    Vector res(this->x / d, this->y / d);
    return res;
}

Vector& Vector::operator/=(const double d) {
    this->x /= d;
    this->y /= d;
    return *this;
}

bool Vector::operator==(const Vector& vec) {
    return this->x == vec.x && this->y == vec.y;
}