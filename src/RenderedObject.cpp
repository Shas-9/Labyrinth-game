#include "RenderedObject.h"

RenderedObject::RenderedObject() : position(Vector(0, 0)), type("") {}

RenderedObject::RenderedObject(Vector position, string type)
    : position(position), type(type) {
  // Create the rectangular object
  this->rectangle = new sf::RectangleShape();

  // Set the size of the object
  this->rectangle->setSize(sf::Vector2f(this->dimensions.getX(),
                                        this->dimensions.getY()));

  // Set the position of the object
  this->rectangle->setPosition(
      sf::Vector2f(this->position.getX(), this->position.getY()));
}

Vector RenderedObject::getPosition() { return this->position; }
Vector RenderedObject::getDimensions() { return this->dimensions; }

bool RenderedObject::collidingWith(RenderedObject* rendered_object) {
  double RectALeft = rendered_object->getPosition().getX();
  double RectARight = rendered_object->getPosition().getX() +
                      rendered_object->getDimensions().getX();

  double RectATop = rendered_object->getPosition().getY();
  double RectABottom = rendered_object->getPosition().getY() +
                       rendered_object->getDimensions().getY();

  double RectBLeft = this->getPosition().getX();
  double RectBRight = this->getPosition().getX() + this->getDimensions().getX();

  double RectBTop = this->getPosition().getY();
  double RectBBottom =
      this->getPosition().getY() + this->getDimensions().getY();

  if (RectALeft < RectBRight && RectARight > RectBLeft &&
      RectATop > RectBBottom && RectABottom < RectBTop)
    // Test if the 2 rendered objects are inside each other
    return true;
  else
    return false;
}

void RenderedObject::render(sf::RenderWindow& window) {
  window.draw(*this->rectangle);
}