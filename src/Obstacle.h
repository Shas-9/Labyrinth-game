#ifndef OBSTACLE_INCLUDE
#define OBSTACLE_INCLUDE

#include "RenderedObject.h"

class Obstacle : public RenderedObject {
 public:
  Obstacle();
  Obstacle(Vector position, string type, Vector dimensions);
  void update();
  void render();
};

#endif