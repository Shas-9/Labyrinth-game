#include "Cat.h"

// Default empty constructor
Cat::Cat() {}

// Constructor that sets the texture of the cat item as it is displayed on screen
Cat::Cat(Vector position, sf::Texture* cat_texture) : Item(position, Vector(200, 135), "cat", "your cat!") {
  double scale = 0.3;
  sf::IntRect* rectSourceSprite = new sf::IntRect(
    0,
    0,
    this->getDimensions().getX() / scale,
    this->getDimensions().getY() / scale
  );
  
  sprite->setTexture(*cat_texture);
  sprite->setTextureRect(*rectSourceSprite);
  sprite->scale(sf::Vector2f(scale, scale));
}