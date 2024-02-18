#include "Block.hpp"

Block::Block() : Renderable(Vector(0, 0), Vector(10, 10)) {}

// The constructor function for the object
Block::Block(Vector position) : Renderable(position, Vector(10, 10)) {
  sf::IntRect* rectSourceSprite = new sf::IntRect(0, 0, this->getDimensions().x / 3, this->getDimensions().y / 3);
  sf::Texture* texture = LOADTEXTURE("textures/blocks/stone.png");
  this->sprite = new sf::Sprite();
  sprite->setTexture(*texture);
  sprite->setTextureRect(*rectSourceSprite);
  sprite->scale(sf::Vector2f(3, 3));
}

// Block update function should do nothing.
// THIS IS LEFT INTENTIONALLY EMPTY
void Block::update() {}