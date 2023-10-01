#ifndef VECTOR_INCLDUE
#define VECTOR_INCLUDE

class Vector {
 private:
  double x;
  double y;

 public:
  Vector(double x, double y);
  void right(int scale);
  void left(int scale);
  void up(int scale);
  void down(int scale);
  double getXPosition();
  double getYPosition();
};

#endif