#include "Obstacle.h"
#include "TexturesHandler.hpp"
#include <iostream>

Obstacle::Obstacle() : RenderedObject(Vector(0, 0), Vector(10, 10), "obstacle") {}

// The constructor function for the object
Obstacle::Obstacle(Vector position, string type, Vector dimensions) : RenderedObject(position, dimensions, type) {
  sf::IntRect* rectSourceSprite = new sf::IntRect(0, 0, this->getDimensions().getX() / 3, this->getDimensions().getY() / 3);
  sf::Texture* texture = LOADTEXTURE("textures/stone_wall.png");
  this->sprite = new sf::Sprite();
  sprite->setTexture(*texture);
  sprite->setTextureRect(*rectSourceSprite);
  sprite->scale(sf::Vector2f(3, 3));

  sf::IntRect* rectSourceSprite2 = new sf::IntRect(0, 0, this->getDimensions().getX() / 3, 20);
  sf::Texture* texture2 = LOADTEXTURE("textures/stone_wall_bottom.png");
  this->bottom_wall_sprite = new sf::Sprite();
  bottom_wall_sprite->setTexture(*texture2);
  bottom_wall_sprite->setTextureRect(*rectSourceSprite2);
  bottom_wall_sprite->scale(sf::Vector2f(3, 3));

  sf::IntRect* rectSourceSprite3 = new sf::IntRect(0, 0, 10, this->getDimensions().getY() / 3);

  sf::Texture* texture3 = LOADTEXTURE("textures/stone_wall_right.png");
  this->right_wall_sprite = new sf::Sprite();
  right_wall_sprite->setTexture(*texture3);
  right_wall_sprite->setTextureRect(*rectSourceSprite3);
  right_wall_sprite->scale(sf::Vector2f(3, 3));

  sf::IntRect* rectSourceSprite4 = new sf::IntRect(0, 0, 16, 32);
  sf::Texture* texture4 = LOADTEXTURE("textures/stone_wall_corner.png");
  this->border_wall_sprite = new sf::Sprite();
  border_wall_sprite->setTexture(*texture4);
  border_wall_sprite->setTextureRect(*rectSourceSprite4);
  border_wall_sprite->scale(sf::Vector2f(2, 1.9));
}

// This function takes in the window object and draws the object
void Obstacle::render(sf::RenderWindow *window, Vector camera_position) {
  this->sprite->setPosition(
    sf::Vector2f(
      this->position.getX() - camera_position.getX(),
      this->position.getY() - camera_position.getY()
    )
  );
  window->draw(*this->sprite);
}

void Obstacle::render_bottom_wall(sf::RenderWindow *window, Vector camera_position) {
  this->bottom_wall_sprite->setPosition(
    sf::Vector2f(
      this->position.getX() - camera_position.getX(),
      this->position.getY() - camera_position.getY() + (this->sprite->getTextureRect().height) * 3
    )
  );
  window->draw(*this->bottom_wall_sprite);

  // render the border
  border_wall_sprite->setPosition(
    sf::Vector2f(
      this->position.getX() - camera_position.getX() + (this->sprite->getTextureRect().width) * 3,
      this->position.getY() - camera_position.getY() + (this->sprite->getTextureRect().height) * 3
    )
  );
  window->draw(*this->border_wall_sprite);
}

void Obstacle::render_right_wall(sf::RenderWindow *window, Vector camera_position) {
  this->right_wall_sprite->setPosition(
    sf::Vector2f(
      this->position.getX() - camera_position.getX() + (this->sprite->getTextureRect().width) * 3,
      this->position.getY() - camera_position.getY()
    )
  );
  window->draw(*this->right_wall_sprite);
}

// Obstacle update function should do nothing.
// THIS IS LEFT INTENTIONALLY EMPTY
void Obstacle::update() {}

void Obstacle::printData(std::ofstream *outfile) {
  (*outfile) << "{ \"position\": [" << this->position.getX() << ", " << this->position.getY() <<
    "], \"dimensions\": [" << this->dimensions.getX() << ", " << this->dimensions.getY() << "]},"
    << std::endl;
}