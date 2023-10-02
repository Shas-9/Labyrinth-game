#ifndef VECTOR_INCLUDE
#define VECTOR_INCLUDE

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

  double getXPosition();
  double getYPosition();

  void setPosition(double x, double y);
  void setPosition(int x, int y);
};

#endif