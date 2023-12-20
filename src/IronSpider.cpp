#include "IronSpider.h"

// Default constructor for player does nothing (Environment required)
IronSpider::IronSpider() {}

IronSpider::IronSpider(
  Vector position,
  Obstacle* obstacles,
  int obstacles_num,
  sf::Texture* iron_spider_texture
) : Enemy(
  position,
  Vector(118, 98),  // Dimensions
  "iron_spider",
  2,                // Speed
  30,               // Health
  10,               // Attack damage
  obstacles,
  obstacles_num,
  40                // Sight distance
) {
  int scale = 4;
  this->walking_frames = Utility::getIronSpiderWalkingFrames(this->getDimensions(), scale);
  sprite->scale(sf::Vector2f(scale, scale));
  sprite->setTexture(*iron_spider_texture);
  sprite->setTextureRect(*this->walking_frames[0][0]);
}