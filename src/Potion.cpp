#include "Potion.h"

Potion::Potion() {}

Potion::Potion(
  Vector position,
  std::string type,
  std::string description,
  int health_regen,
  sf::Texture* texture
) : Item(position, Vector(45, 60), type, description),
health_regen(health_regen) {
  this->dimensions = Vector(45, 60);
  sf::IntRect* rectSourceSprite = new sf::IntRect(4, 0, this->getDimensions().getX() / 2, this->getDimensions().getY() / 2);
  sprite->setTexture(*texture);
  sprite->setTextureRect(*rectSourceSprite);
  sprite->scale(sf::Vector2f(2, 2));
}

int Potion::getHealthRegen() {
  return this->health_regen;
}

// void Potion::update() {}