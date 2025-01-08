#ifndef AREA_SHAPE_INCLUDE
#define AREA_SHAPE_INCLUDE

#include "Vector.h"

struct AreaRect {
  AreaRect();
  AreaRect(double x, double y, double w, double h);
  AreaRect(const Vector pos, const Vector size);

  bool contains(const Vector& point) const;
  bool contains(const AreaRect& rect) const;
  bool overlap(const AreaRect& rect) const;
  bool contains(const struct AreaCirc& circ) const;
  bool overlap(const struct AreaCirc& circ) const;

  Vector pos;
  Vector size;
};

struct AreaCirc {
  AreaCirc();
  AreaCirc(double x, double y, double radius);
  AreaCirc(const Vector pos, double radius);

  bool contains(const Vector& point) const;
  bool contains(const AreaCirc& circ) const;
  bool overlap(const AreaCirc& circ) const;
  bool contains(const AreaRect& rect) const;
  bool overlap(const AreaRect& rect) const;

  Vector pos;
  double radius;
};

#endif