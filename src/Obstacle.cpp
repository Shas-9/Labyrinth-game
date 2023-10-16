#include "Obstacle.h"

#include <iostream>


Obstacle::Obstacle()
  : RenderedObject(Vector(0, 0), Vector(10, 10), "obstacle") {}

// The constructor function for the object
Obstacle::Obstacle(Vector position, string type, Vector dimensions, sf::Texture* texture)
  : RenderedObject(position, dimensions, type) {
  sf::IntRect* rectSourceSprite = new sf::IntRect(0, 0, this->getDimensions().getX() / 3, this->getDimensions().getY() / 3);
  this->sprite = new sf::Sprite();
  sprite->setTexture(*texture);
  sprite->setTextureRect(*rectSourceSprite);
  sprite->scale(sf::Vector2f(3, 3));
}

// This function takes in the window object and draws the object
void Obstacle::render(sf::RenderWindow *window, Vector camera_position) {
  this->sprite->setPosition(
    sf::Vector2f(this->position.getX() - camera_position.getX() + 500, this->position.getY() - camera_position.getY() + 400)
  );
  window->draw(*this->sprite);
}

// Obstacle update function should do nothing.
// THIS IS LEFT INTENTIONALLY EMPTY
void Obstacle::update() {}

void Obstacle::printData(std::ofstream *outfile) {
  (*outfile) << "{ \"position\": [" << this->position.getX() << ", " << this->position.getY() <<
    "], \"dimensions\": [" << this->dimensions.getX() << ", " << this->dimensions.getY() << "]},"
    << std::endl;
}