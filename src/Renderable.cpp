#include "Renderable.h"
#include "singleton/ScreenManager.h"
#include "TexturesHandler.hpp"
#include <iostream>

Renderable::Renderable() : position(Vector(0, 0)), type("") {}

Renderable::Renderable(Vector position, Vector dimensions, string type)
  : position(position), dimensions(dimensions), type(type) {}

Vector Renderable::getPosition() { return this->position; }
Vector Renderable::getDimensions() { return this->dimensions; }
void Renderable::setPosition(Vector new_position) { this->position = new_position; }

bool Renderable::isCollidingWithObject(Renderable* renderable) {
  bool A_above_B = renderable->getPosition().getY() >= this->getPosition().getY() + this->getDimensions().getY();
  bool A_below_B = renderable->getPosition().getY() + renderable->getDimensions().getY() <= this->getPosition().getY();
  bool A_right_of_B = renderable->getPosition().getX() + renderable->getDimensions().getX() <= this->getPosition().getX();
  bool A_left_of_B = renderable->getPosition().getX() >= this->getPosition().getX() + this->getDimensions().getX();

  bool notColliding = A_above_B || A_below_B || A_right_of_B || A_left_of_B;
  return !notColliding;
}

void Renderable::render(std::shared_ptr<Camera> cam) {
  Vector sprite_pos = cam->convertPos(this->getPosition());
  this->sprite->setPosition(sf::Vector2f(sprite_pos.x, sprite_pos.y));
  
  if (this->type == "static") {
    this->sprite->setScale(sf::Vector2f(this->dimensions.x / this->texture_rect.getSize().x * cam->getZoom(), this->dimensions.y / this->texture_rect.getSize().y * cam->getZoom()));
  }

  if (this->type == "animation") {
    this->sprite->setTextureRect(this->anim_controller->getTextureRect());
    this->sprite->setScale(sf::Vector2f(this->dimensions.x / this->anim_controller->getTextureRect().getSize().x * cam->getZoom(), this->dimensions.y / this->anim_controller->getTextureRect().getSize().y * cam->getZoom()));
  }

  ScreenManager::getInstance().window_ptr->draw(*this->sprite);
}

void Renderable::setTexture(std::string texture_location) {
  this->sprite = std::make_shared<sf::Sprite>();
  sf::Texture* texture = LOADTEXTURE(texture_location);
  this->sprite->setTexture(*texture);
}

void Renderable::registerAnimController(std::shared_ptr<AnimController> anim_controller) {
  this->anim_controller = anim_controller;
  this->type = "animation";
}

std::shared_ptr<AnimController> Renderable::getAnimController() {
  return this->anim_controller;
}

void Renderable::registerStaticSprite(Vector texture_dim) {
  this->texture_rect = sf::IntRect(0, 0, texture_dim.x, texture_dim.y);
  this->sprite->setTextureRect(this->texture_rect);
  this->type = "static";
}