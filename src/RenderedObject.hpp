#ifndef RENDERED_OBJECT_INCLUDE
#define RENDERED_OBJECT_INCLUDE

#include <SFML/Graphics.hpp>
#include <string>

using std::string;

#include "Vector.hpp"

class RenderedObject {
 protected:
  Vector position;
  Vector dimensions;
  string type;
  sf::RectangleShape* rectangle;

 public:
  RenderedObject();
  RenderedObject(Vector position, Vector dimensions, string type);

  
  bool isCollidingWithObject(RenderedObject* rendered_object);

  Vector getPosition();
  void setPosition(Vector new_position);
  
  Vector getDimensions();

  void render(sf::RenderWindow* window);
  virtual void update() = 0;

  sf::RectangleShape* getRectangle();
};

#endif