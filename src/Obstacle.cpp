#include "Obstacle.h"

#include <iostream>


Obstacle::Obstacle()
  : RenderedObject(Vector(0, 0), "obstacle"), dimensions(Vector(10, 10)) {}

// The constructor function for the object
Obstacle::Obstacle(Vector position, string type, Vector dimensions)
  : RenderedObject(position, type), dimensions(dimensions) {
  // Create the rectanglular obstacle object
  this->rectangle = new sf::RectangleShape();

  // Set the size of the obstacle
  this->rectangle->setSize(
    sf::Vector2f(this->dimensions.getX(), this->dimensions.getY()));

  // Set the position of the obstacle
  this->rectangle->setPosition(
    sf::Vector2f(this->position.getX(), this->position.getY()));
}

// This function takes in the window object and draws the object
void Obstacle::render(sf::RenderWindow &window) {
  window.draw(*this->rectangle);
}

// Obstacle update function should do nothing.
// THIS IS LEFT INTENTIONALLY EMPTY
void Obstacle::update() {}

void Obstacle::printData(std::ofstream *outfile) {
  (*outfile) << "{ \"position\": [" << this->position.getX() << ", " << this->position.getY() << 
            "], \"dimensions\": [" << this->dimensions.getX() << ", " << this->dimensions.getY() << "]}," 
            << std::endl;
}