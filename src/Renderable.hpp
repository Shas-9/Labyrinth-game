#ifndef RENDERABLE_INCLUDE
#define RENDERABLE_INCLUDE

#include <SFML/Graphics.hpp>
#include "Utility.h"
#include "TexturesHandler.hpp"
#include "Vector.h"

using std::string;


class Renderable {
protected:
  Vector position;
  Vector dimensions;
  sf::Sprite* sprite;

public:
  Renderable();
  Renderable(Vector position, Vector dimensions);

  bool isCollidingWithObject(Renderable* rendered_object);

  Vector getPos();
  void setPos(Vector new_position);

  Vector getDimensions();

  void render();
  virtual void update() = 0;
};

#endif