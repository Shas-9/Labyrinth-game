#ifndef VECTOR_INCLUDE
#define VECTOR_INCLUDE

class Vector {
private:

public:
  double x;
  double y;
  
  Vector();
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

struct AreaRect {
  AreaRect() {
    this->pos = Vector(0, 0);
    this->size = Vector(1, 1);
  }
  AreaRect(double x, double y, double w, double h) {
    this->pos = Vector(x, y);
    this->size = Vector(w, h);
  }
  AreaRect(const Vector pos, const Vector size) {
    this->pos = pos;
    this->size = size;
  }
  bool contains(const Vector& point) const {
    bool x_axis = this->pos.x < point.x && this->pos.x + this->size.x > point.x;
    bool y_axis = this->pos.y < point.y && this->pos.y + this->size.y > point.y;
    return x_axis && y_axis;
  }
  bool contains(const AreaRect& rect) const {
    bool x_axis = this->pos.x < rect.pos.x && this->pos.x + this->size.x > rect.pos.x + rect.size.x;
    bool y_axis = this->pos.y < rect.pos.y && this->pos.y + this->size.y > rect.pos.y + rect.size.y;
    return x_axis && y_axis;
  }
  bool overlap(const AreaRect& rect) const {
    bool A_above_B = rect.pos.y >= this->pos.y + this->size.y;
    bool A_below_B = rect.pos.y + rect.size.y <= this->pos.y;
    bool A_right_of_B = rect.pos.x + rect.size.x <= this->pos.x;
    bool A_left_of_B = rect.pos.x >= this->pos.x + this->size.x;

    bool notColliding = A_above_B || A_below_B || A_right_of_B || A_left_of_B;
    return !notColliding;
  }
  Vector pos;
  Vector size;
};

#endif