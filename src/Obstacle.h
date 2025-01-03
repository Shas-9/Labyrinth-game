#ifndef OBSTACLE_INCLUDE
#define OBSTACLE_INCLUDE

#include <SFML/Graphics.hpp>
#include <fstream>

#include "RenderedObject.h"
#include <memory>
#include "Camera.h"

class Obstacle : public RenderedObject {
private:
  sf::Sprite* sprite;
  sf::Sprite* bottom_wall_sprite;
  sf::Sprite* right_wall_sprite;
  sf::Sprite* border_wall_sprite;

public:
  Obstacle();
  Obstacle(Vector position, string type, Vector dimensions);
  void update();
  void render(std::shared_ptr<Camera> cam);
  void render_bottom_wall(std::shared_ptr<Camera> cam);
  void render_right_wall(std::shared_ptr<Camera> cam);
  void printData(std::ofstream* outfile);
};

#endif