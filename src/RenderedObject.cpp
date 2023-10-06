#include "RenderedObject.h"

RenderedObject::RenderedObject() : position(Vector(0, 0)), type("") {}

RenderedObject::RenderedObject(Vector position, string type)
    : position(position), type(type) {}

Vector RenderedObject::getPosition() { return this->position; }
Vector RenderedObject::getDimentions() { this->dimensions; }

bool collidingWith(RenderedObject* rendered_object) {
  // Test if the 2 rendered objects are inside each other
}