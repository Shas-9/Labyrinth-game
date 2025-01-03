#include "Item.h"
#include "singleton/ScreenManager.h"

Item::Item() {}

Item::Item(Vector position,
  Vector dimensions,
  std::string type,
  std::string description
) : RenderedObject(position, dimensions, type), description(description) {
  this->sprite = new sf::Sprite();
}

void Item::render(std::shared_ptr<Camera> cam) {
  Vector sprite_pos = cam->convertPos(this->getPosition());
  this->sprite->setPosition(sf::Vector2f(sprite_pos.x, sprite_pos.y));
  
  ScreenManager::getInstance().window_ptr->draw(*this->sprite);
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