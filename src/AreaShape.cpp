#include "AreaShape.h"

// AreaRect Implementations
AreaRect::AreaRect() : pos({0, 0}), size({1, 1}) {}

AreaRect::AreaRect(double x, double y, double w, double h) : pos({x, y}), size({w, h}) {}

AreaRect::AreaRect(const Vector pos, const Vector size) : pos(pos), size(size) {}

bool AreaRect::contains(const Vector& point) const {
  bool x_axis = this->pos.x <= point.x && this->pos.x + this->size.x >= point.x;
  bool y_axis = this->pos.y <= point.y && this->pos.y + this->size.y >= point.y;
  return x_axis && y_axis;
}

bool AreaRect::contains(const AreaRect& rect) const {
  bool x_axis = this->pos.x <= rect.pos.x && this->pos.x + this->size.x >= rect.pos.x + rect.size.x;
  bool y_axis = this->pos.y <= rect.pos.y && this->pos.y + this->size.y >= rect.pos.y + rect.size.y;
  return x_axis && y_axis;
}

bool AreaRect::overlap(const AreaRect& rect) const {
  bool A_above_B = rect.pos.y >= this->pos.y + this->size.y;
  bool A_below_B = rect.pos.y + rect.size.y <= this->pos.y;
  bool A_right_of_B = rect.pos.x + rect.size.x <= this->pos.x;
  bool A_left_of_B = rect.pos.x >= this->pos.x + this->size.x;

  bool notColliding = A_above_B || A_below_B || A_right_of_B || A_left_of_B;
  return !notColliding;
}

bool AreaRect::contains(const AreaCirc& circ) const {
  Vector circ_center = circ.pos + Vector(circ.radius, circ.radius);
  bool left_point = this->contains(circ_center - Vector(circ.radius, 0.0));
  bool right_point = this->contains(circ_center + Vector(circ.radius, 0.0));
  bool top_point = this->contains(circ_center - Vector(0.0, circ.radius));
  bool bottom_point = this->contains(circ_center + Vector(0.0, circ.radius));
  return left_point && right_point && top_point && bottom_point;
}

bool AreaRect::overlap(const AreaCirc& circ) const {
  // Calc actual center of the circle
  Vector circ_center = circ.pos + Vector(circ.radius, circ.radius);
  
  AreaRect vertical_rect(this->pos - Vector(0.0, circ.radius), this->size + Vector(0.0, circ.radius*2));
  AreaRect horizontal_rect(this->pos - Vector(circ.radius, 0.0), this->size + Vector(circ.radius*2, 0.0));
  
  AreaCirc top_right_circ(this->pos + Vector(this->size.x, 0.0) - Vector(circ.radius, circ.radius), circ.radius);
  AreaCirc top_left_circ(this->pos - Vector(circ.radius, circ.radius), circ.radius);
  AreaCirc bottom_left_circ(this->pos + Vector(0.0, this->size.y) - Vector(circ.radius, circ.radius), circ.radius);
  AreaCirc bottom_right_circ(this->pos + this->size - Vector(circ.radius, circ.radius), circ.radius);

  return vertical_rect.contains(circ_center) || horizontal_rect.contains(circ_center) || 
    top_right_circ.contains(circ_center) || top_left_circ.contains(circ_center) || 
    bottom_left_circ.contains(circ_center) || bottom_right_circ.contains(circ_center);
}

// AreaCirc Implementations
AreaCirc::AreaCirc() : pos({0, 0}), radius(1) {}

AreaCirc::AreaCirc(double x, double y, double radius) : pos({x, y}), radius(radius) {}

AreaCirc::AreaCirc(const Vector pos, double radius) : pos(pos), radius(radius) {}

bool AreaCirc::contains(const Vector& point) const {
  Vector circ_center = this->pos + Vector(this->radius, this->radius);
  return (circ_center - point).getLength() <= radius;
}

bool AreaCirc::contains(const AreaCirc& circ) const {
  Vector circ_center = circ.pos + Vector(circ.radius, circ.radius);
  Vector own_center = this->pos + Vector(this->radius, this->radius);
  return (circ_center - own_center).getLength() + circ.radius <= this->radius;
}

bool AreaCirc::overlap(const AreaCirc& circ) const {
  Vector circ_center = circ.pos + Vector(circ.radius, circ.radius);
  Vector own_center = this->pos + Vector(this->radius, this->radius);
  return (circ_center - own_center).getLength() <= this->radius + circ.radius;
}

bool AreaCirc::contains(const AreaRect& rect) const {
  bool top_left_corner = this->contains(rect.pos);
  bool top_right_corner = this->contains(rect.pos + Vector(rect.size.x, 0.0));
  bool bottom_left_corner = this->contains(rect.pos + Vector(0.0, rect.size.y));
  bool bottom_right_corner = this->contains(rect.pos + rect.size);
  return top_left_corner && top_right_corner && bottom_left_corner && bottom_right_corner;
}

bool AreaCirc::overlap(const AreaRect& rect) const {
  // Calc actual center of the circle
  Vector circ_center = this->pos + Vector(this->radius, this->radius);
  
  AreaRect vertical_rect(rect.pos - Vector(0.0, this->radius), rect.size + Vector(0.0, this->radius*2));
  AreaRect horizontal_rect(rect.pos - Vector(this->radius, 0.0), rect.size + Vector(this->radius*2, 0.0));
  
  AreaCirc top_right_circ(rect.pos + Vector(rect.size.x, 0.0) - Vector(this->radius, this->radius), this->radius);
  AreaCirc top_left_circ(rect.pos - Vector(this->radius, this->radius), this->radius);
  AreaCirc bottom_left_circ(rect.pos + Vector(0.0, rect.size.y) - Vector(this->radius, this->radius), this->radius);
  AreaCirc bottom_right_circ(rect.pos + rect.size - Vector(this->radius, this->radius), this->radius);

  return vertical_rect.contains(circ_center) || horizontal_rect.contains(circ_center) || 
    top_right_circ.contains(circ_center) || top_left_circ.contains(circ_center) || 
    bottom_left_circ.contains(circ_center) || bottom_right_circ.contains(circ_center);
}