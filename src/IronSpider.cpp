#include "IronSpider.h"

// Default constructor for player does nothing (Environment required)
IronSpider::IronSpider() {}

IronSpider::IronSpider(
  Vector position,
  int movement_speed,
  int health,
  int attack_damage,
  Obstacle* obstacles,
  int obstacles_num,
  int sight_distance,
  sf::Texture* iron_spider_texture
) : Enemy(
  position,
  Vector(118, 98),
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

// void IronSpider::render(sf::RenderWindow *window, Vector screen_dimensions, Vector camera_position) {
//   Utility::frames_handler(
//     this->sprite,
//     &this->current_frames_index,
//     &this->current_animation_frame,
//     walking_frames,
//     moving_left,
//     moving_right,
//     moving_up,
//     moving_down,
//     20
//   );

//   this->sprite->setPosition(
//     this->position.getX() - camera_position.getX() + screen_dimensions.getX(),
//     this->position.getY() - camera_position.getY() + screen_dimensions.getY()
//   );
//   window->draw(*this->sprite);
// }

// void IronSpider::update() {
  
// }
