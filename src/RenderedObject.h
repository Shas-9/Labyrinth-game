#ifndef RENDERED_OBJECT_INCLUDE
#define RENDERED_OBJECT_INCLUDE

#include <SFML/Graphics.hpp>
#include <string>

using std::string;

#include "Vector.h"

class RenderedObject {
 protected:
  Vector position;
  Vector dimensions;
  string type;
  sf::RectangleShape* rectangle;

 public:
  RenderedObject();
  RenderedObject(Vector position, string type);

  /** NEWLY ADDED FUNCTIONS*/
  bool collidingWith(RenderedObject* rendered_object);

  Vector getPosition();
  Vector getDimensions();
  /** */

  void render(sf::RenderWindow& window);
  virtual void update() = 0;
};

#endif