#include "IronSpider.h"

// Default constructor for player does nothing (Environment required)
IronSpider::IronSpider() {}

IronSpider::IronSpider(
  Vector position,
  int movement_speed,
  int health,
  int attack_damage,
  Obstacle* obstacles,
  int sight_distance,
  sf::Texture* iron_spider_texture
) : Enemy(
  position,
  Vector(100, 100),
  "iron_spider",
  movement_speed,
  health,
  attack_damage,
  obstacles,
  obstacles_num,
  sight_distance
) {
  int scale = 4;
  this->walking_frames = Utility::getIronSpiderWalkingFrames(this->getDimensions(), scale);
  sprite->scale(sf::Vector2f(scale, scale));
  sprite->setTexture(*iron_spider_texture);
  sprite->setTextureRect(*this->walking_frames[0][0]);
}

void IronSpider::render(sf::RenderWindow *window) {
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

  this->sprite->setPosition(sf::Vector2f(500, 400));
  window->draw(*this->sprite);
}

void IronSpider::update() {}
