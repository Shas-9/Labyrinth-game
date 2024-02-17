#ifndef OBSTACLE_INCLUDE
#define OBSTACLE_INCLUDE

#include <SFML/Graphics.hpp>
#include <fstream>

#include "RenderedObject.h"

class Obstacle : public RenderedObject {
private:
  sf::Sprite* sprite;

public:
  Obstacle();
  Obstacle(Vector position, string type, Vector dimensions);
  void update();
  void render(sf::RenderWindow* window, Vector camera_position);
  void printData(std::ofstream* outfile);
};

#endif