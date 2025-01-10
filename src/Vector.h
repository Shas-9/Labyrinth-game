#ifndef VECTOR_INCLUDE
#define VECTOR_INCLUDE

#include <SFML/Graphics.hpp>

class Vector {
private:

public:
  double x;
  double y;
  
  Vector();
  Vector(sf::Vector2f v);
  Vector(double x, double y);
  Vector(float x, float y);
  Vector(int x, int y);
  Vector(unsigned int x, unsigned int y);

  double getX() const;
  double getY() const;

  void set(double x, double y);
  void set(int x, int y);

  double getLength() const;
  void normalize();

  static Vector getMid(const Vector& vec1, const Vector& vec2, double delay);
  static Vector getMid(const Vector& vec1, const Vector& vec2);

  void print() const;

  Vector operator+(const Vector& vec) const;
  Vector& operator+=(const Vector& vec);
  Vector operator-(const Vector& vec) const;
  Vector& operator-=(const Vector& vec);
  Vector operator*(const double d) const;
  Vector& operator*=(const double d);
  Vector operator/(const double d) const;
  Vector& operator/=(const double d);
  bool operator==(const Vector& vec) const;
};

#endif