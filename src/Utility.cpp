#include "Utility.h"

void Utility::setObstacleTexture() {
  this->texture = new sf::Texture();
  texture->loadFromFile("textures/stone_wall.png", sf::IntRect(10, 10, 32, 32));
  texture->setRepeated(true);
}
sf::Texture* Utility::getObstacleTexture() {
  return this->texture;
}