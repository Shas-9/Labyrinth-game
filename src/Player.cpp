#include "Player.h"
#include "TexturesHandler.hpp"
#include <iostream>
#include "singleton/ScreenManager.h"

#define SCREEN_X ScreenManager::getInstance().screen_dimensions.x
#define SCREEN_Y ScreenManager::getInstance().screen_dimensions.y

// Default constructor for player does nothing (Environment required)
Player::Player() {}

Player::Player(
  Vector position,
  Vector dimensions,
  string type,
  int movement_speed,
  int health,
  int attack_damage,
  std::shared_ptr<Environment> environment
) : Entity(
  position,
  dimensions,
  type,
  movement_speed,
  health,
  attack_damage,
  environment->getObstacles(),
  environment->getObstaclesNum()
), environment(environment) {
  int scale = dimensions.getX()/14;
  this->walking_frames = Utility::getPlayerWalkingFrames(this->getDimensions(), scale);
  sprite->scale(sf::Vector2f(scale, scale));
  sf::Texture* texture = LOADTEXTURE("textures/player.png");
  sprite->setTexture(*texture);
  sprite->setTextureRect(*this->walking_frames[0][0]);
}

// Get player's score
int Player::getScore() {
  return this->score;
}

void Player::render(std::shared_ptr<Camera> cam) {
  Utility::frames_handler(
    this->sprite,
    &this->current_frames_index,
    &this->current_animation_frame,
    walking_frames,
    moving_left,
    moving_right,
    moving_up,
    moving_down,
    movement_speed*8
  );

  Vector sprite_pos = cam->convertPos(this->getPosition());
  this->sprite->setPosition(sf::Vector2f(sprite_pos.x, sprite_pos.y));

  int scale = dimensions.getX()/14;
  this->sprite->setScale(sf::Vector2f(scale * cam->getZoom(), scale * cam->getZoom()));
  
  ScreenManager::getInstance().window_ptr->draw(*this->sprite);
}

void Player::update() {
  // Player movement
  if (this->getMovementDirection(0)) this->moveLeft();
  if (this->getMovementDirection(1)) this->moveRight();
  if (this->getMovementDirection(2)) this->moveUp();
  if (this->getMovementDirection(3)) this->moveDown();
}