#include "RenderedObject.hpp"
#include <iostream>

RenderedObject::RenderedObject() : position(Vector(0, 0)), type("") {}

RenderedObject::RenderedObject(Vector position, Vector dimensions, string type)
  : position(position), dimensions(dimensions), type(type) {
  // Create the rectangular object
  this->rectangle = new sf::RectangleShape();

  // Set the size of the object
  this->rectangle->setSize(sf::Vector2f(this->dimensions.x, this->dimensions.y));

  // Set the position of the object
  this->rectangle->setPosition(sf::Vector2f(this->position.x, this->position.y));
}

Vector RenderedObject::getPosition() { return this->position; }
Vector RenderedObject::getDimensions() { return this->dimensions; }

bool RenderedObject::isCollidingWithObject(RenderedObject* rendered_object) {
  bool object_A_above_B = rendered_object->getPosition().y >= this->getPosition().y + this->getDimensions().y;

  bool object_A_below_B = rendered_object->getPosition().y + rendered_object->getDimensions().y <= this->getPosition().y;

  bool object_A_right_of_B = rendered_object->getPosition().x + rendered_object->getDimensions().x <= this->getPosition().x;

  bool object_A_left_of_B = rendered_object->getPosition().x >= this->getPosition().x + this->getDimensions().x;


  bool notColliding = object_A_above_B || object_A_below_B || object_A_right_of_B || object_A_left_of_B;


  return !notColliding;
}

void RenderedObject::render(sf::RenderWindow* window) {
  window->draw(*this->rectangle);
}

void RenderedObject::setPosition(Vector new_position) {
  this->position = new_position;
}

sf::RectangleShape* RenderedObject::getRectangle() {
  return this->rectangle;
}