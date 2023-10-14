#ifndef OBSTACLE_INCLUDE
#define OBSTACLE_INCLUDE

#include <SFML/Graphics.hpp>

#include "RenderedObject.h"

class Obstacle : public RenderedObject {
 private:
  Vector dimensions;
  sf::RectangleShape* rectangle;

 public:
  Obstacle();
  Obstacle(Vector position, string type, Vector dimensions);
  void update();
  void render(sf::RenderWindow& window);
};

#endif