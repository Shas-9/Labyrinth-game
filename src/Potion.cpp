#include "Potion.h"
#include "TexturesHandler.hpp"

Potion::Potion() {}

Potion::Potion(Vector position) : Item(position, Vector(45, 60), "health", "a health potion"),
health_regen(health_regen) {
  this->dimensions = Vector(45, 60);
  sf::IntRect* rectSourceSprite = new sf::IntRect(4, 0, this->getDimensions().getX() / 2, this->getDimensions().getY() / 2);
  sf::Texture* test = LOADTEXTURE("textures/potion.png");
  sprite->setTexture(*test);
  sprite->setTextureRect(*rectSourceSprite);
  sprite->scale(sf::Vector2f(2, 2));
}