#ifndef RENDERED_OBJECT_INCLUDE
#define RENDERED_OBJECT_INCLUDE

#include <string>
using namespace std;

#include "Vector.h"

class RenderedObject {
 protected:
  Vector position;
  Vector dimensions;
  string type;

 public:
  RenderedObject();
  RenderedObject(Vector position, string type);

  /** NEWLY ADDED FUNCTIONS*/
  bool collidingWith(RenderedObject* rendered_object);

  Vector getPosition();
  Vector getDimensions();
  /** */

  virtual void render() = 0;
  virtual void update() = 0;
};

#endif