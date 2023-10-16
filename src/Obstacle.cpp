#include "Obstacle.h"

#include <iostream>


Obstacle::Obstacle()
  : RenderedObject(Vector(0, 0), Vector(10, 10), "obstacle") {}

// The constructor function for the object
Obstacle::Obstacle(Vector position, string type, Vector dimensions)
  : RenderedObject(position, dimensions, type) {
  // std::cout << "Obstacle {" << this->dimensions.getX() << ", " << this->dimensions.getY() << "}" << std::endl;
  // Create the rectanglular obstacle object
  this->rectangle = new sf::RectangleShape();

  // Set the size of the obstacle
  this->rectangle->setSize(sf::Vector2f(this->dimensions.getX(), this->dimensions.getY()));

  // Set the position of the obstacle
  this->rectangle->setPosition(sf::Vector2f(this->position.getX(), this->position.getY()));


  sf::Texture* texture = new sf::Texture();
  texture->create(100, 100);
  texture->loadFromFile("textures/stone_wall.png");
  // texture.
  
  texture->setRepeated(true);
  

  // sf::IntRect* rectSourceSprite = new sf::IntRect(0, 0, 10, 10);
  // sf::Sprite *sprite = new sf::Sprite(*texture, *rectSourceSprite);



  this->rectangle->setTexture(texture, true);
}

// This function takes in the window object and draws the object
void Obstacle::render(sf::RenderWindow *window, Vector camera_position) {
  this->rectangle->setPosition(
    sf::Vector2f(this->position.getX() - camera_position.getX() + 500, this->position.getY() - camera_position.getY() + 400)
  );
  window->draw(*this->rectangle);
}

// Obstacle update function should do nothing.
// THIS IS LEFT INTENTIONALLY EMPTY
void Obstacle::update() {}

void Obstacle::printData(std::ofstream *outfile) {
  (*outfile) << "{ \"position\": [" << this->position.getX() << ", " << this->position.getY() <<
    "], \"dimensions\": [" << this->dimensions.getX() << ", " << this->dimensions.getY() << "]},"
    << std::endl;
}