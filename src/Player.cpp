#include "Player.h"
#include <iostream>

// Default constructor for player does nothing (Environment required)
Player::Player() {}

Player::Player(
  Vector position,
  Vector dimensions,
  string type,
  int movement_speed,
  int health,
  int attack_damage,
  Environment* environment,
  sf::Texture* player_texture
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
  sprite->setTexture(*player_texture);
  sprite->setTextureRect(*this->walking_frames[0][0]);
}

// Get player's score
int Player::getScore() {
  return this->score;
}

void Player::render(sf::RenderWindow *window, Vector screen_dimensions) {
  Utility::frames_handler(
    this->sprite,
    &this->current_frames_index,
    &this->current_animation_frame,
    walking_frames,
    moving_left,
    moving_right,
    moving_up,
    moving_down,
    20
  );

  this->sprite->setPosition(
    sf::Vector2f(
      (screen_dimensions.getX() - this->getDimensions().getX()) / 2,
      (screen_dimensions.getY() - this->getDimensions().getY()) / 2
    )
  );
  window->draw(*this->sprite);
}

void Player::update() {}