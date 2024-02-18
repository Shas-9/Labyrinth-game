#include "Renderable.hpp"
#include <iostream>

Renderable::Renderable() : position(Vector(0, 0)) {}

Renderable::Renderable(Vector position, Vector dimensions) : position(position), dimensions(dimensions) {}

Vector Renderable::getPos() { return this->position; }
Vector Renderable::getDimensions() { return this->dimensions; }

bool Renderable::isCollidingWithObject(Renderable* rendered_object) {
  bool object_A_above_B = rendered_object->getPos().x >= this->getPos().y + this->getDimensions().y;
  bool object_A_below_B = rendered_object->getPos().y + rendered_object->getDimensions().y <= this->getPos().y;
  bool object_A_right_of_B = rendered_object->getPos().x + rendered_object->getDimensions().x <= this->getPos().x;
  bool object_A_left_of_B = rendered_object->getPos().x >= this->getPos().x + this->getDimensions().x;

  bool notColliding = object_A_above_B || object_A_below_B || object_A_right_of_B || object_A_left_of_B;

  return !notColliding;
}

void Renderable::render() {
  this->sprite->setPosition(
    sf::Vector2f(
      this->position.x - UTIL_CLASS.getCameraPos()->x,
      this->position.y - UTIL_CLASS.getCameraPos()->y
    )
  );
  UTIL_CLASS.getRenderWindow()->draw(*this->sprite);
}

void Renderable::setPos(Vector new_position) {
  this->position = new_position;
}