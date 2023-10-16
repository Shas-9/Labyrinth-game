#include "RenderedObject.h"
#include <iostream>

RenderedObject::RenderedObject() : position(Vector(0, 0)), type("") {}

RenderedObject::RenderedObject(Vector position, Vector dimensions, string type)
  : position(position), dimensions(dimensions), type(type) {
  // Create the rectangular object
  this->rectangle = new sf::RectangleShape();

  // Set the size of the object
  this->rectangle->setSize(sf::Vector2f(this->dimensions.getX(), this->dimensions.getY()));

  // Set the position of the object
  this->rectangle->setPosition(sf::Vector2f(this->position.getX(), this->position.getY()));
}

Vector RenderedObject::getPosition() { return this->position; }
Vector RenderedObject::getDimensions() { return this->dimensions; }

bool RenderedObject::collidingWith(RenderedObject* rendered_object) {
  bool object_A_above_B = rendered_object->getPosition().getY() >= this->getPosition().getY() + this->getDimensions().getY();

  bool object_A_below_B = rendered_object->getPosition().getY() + rendered_object->getDimensions().getY() <= this->getPosition().getY();

  bool object_A_right_of_B = rendered_object->getPosition().getX() + rendered_object->getDimensions().getX() <= this->getPosition().getX();

  bool object_A_left_of_B = rendered_object->getPosition().getX() >= this->getPosition().getX() + this->getDimensions().getX();


  bool notColliding = object_A_above_B || object_A_below_B || object_A_right_of_B || object_A_left_of_B;


  return !notColliding;
}

void RenderedObject::render(sf::RenderWindow* window) {
  window->draw(*this->rectangle);
}