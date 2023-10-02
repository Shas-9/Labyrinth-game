#include "RenderedObject.h"

RenderedObject::RenderedObject() : position(Vector(0, 0)), type("") {}

RenderedObject::RenderedObject(Vector position, string type)
    : position(position), type(type) {}