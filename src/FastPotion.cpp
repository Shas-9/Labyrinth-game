#include "FastPotion.h"

FastPotion::FastPotion() {}

FastPotion::FastPotion(
  Vector position,
  sf::Texture* texture
) : Item(position, Vector(45, 60), "fast", "a speed potion"), speedBoost(speedBoost) {

  this->dimensions = Vector(60, 45);
  sf::IntRect* rectSourceSprite = new sf::IntRect(4, 0, this->getDimensions().getX() / 2, this->getDimensions().getY() / 2);
  sprite->setTexture(*texture);
  sprite->setTextureRect(*rectSourceSprite);
  sprite->scale(sf::Vector2f(2, 2));

}