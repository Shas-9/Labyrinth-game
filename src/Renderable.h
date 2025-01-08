#ifndef RENDERABLE_INCLUDE
#define RENDERABLE_INCLUDE

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
using std::string;

#include "Vector.h"
#include "Camera.h"
#include "AnimController.h"

class Renderable {
 protected:
  Vector position;
  Vector dimensions;
  string type;
  std::shared_ptr<sf::Sprite> sprite;
  Vector texture_dim;
  sf::IntRect texture_rect;
  std::shared_ptr<AnimController> anim_controller;

 public:
  
  Renderable();
  Renderable(Vector position, Vector dimensions, string type);

  Vector getDimensions();
  Vector getPosition();
  void setPosition(Vector new_position);

  void render(std::shared_ptr<Camera> cam);

  void setTexture(std::string texture_location);
  void registerAnimController(std::shared_ptr<AnimController> anim_controller);
  void registerStaticSprite(Vector texture_dim);

  std::shared_ptr<AnimController> getAnimController();
};

#endif