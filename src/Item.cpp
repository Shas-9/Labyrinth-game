#include "Item.hpp"

Item::Item() {}

Item::Item(Vector position,
  Vector dimensions,
  std::string type,
  std::string description
) : RenderedObject(position, dimensions, type), description(description) {
  this->sprite = new sf::Sprite();
}

void Item::render(sf::RenderWindow *window, Vector camera_position) {
  this->sprite->setPosition(
    sf::Vector2f(
      this->position.getX() - camera_position.getX(),
      this->position.getY() - camera_position.getY()
    )
  );
  window->draw(*this->sprite);
}

std::string Item::getType() {
  return this->type;
}

int Item::getValue() {
  return 0;
}

bool Item::isInObstacle(Obstacle* obstacles, int obstacles_num) {
  // Loop over all obstacles and check if player is running into them
  for (int i = 0; i < obstacles_num; i++) {
    if (this->isCollidingWithObject(&(obstacles[i]))) {
      // If player is colliding with an obstacle, go back to old position.
      return false;
    }
  }
  return true;
}

void Item::update() {}