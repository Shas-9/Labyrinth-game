#ifndef RENDERED_OBJECT_INCLUDE
#define RENDERED_OBJECT_INCLUDE

#include <string>
using namespace std;

#include "Vector.h"

class RenderedObject {
 protected:
  Vector position;
  string type;

 public:
  RenderedObject();
  RenderedObject(Vector position, string type);
  virtual void render() = 0;
  virtual void update() = 0;
};

#endif