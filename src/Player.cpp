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
  int scale = 4;
  this->walking_frames = Utility::getIronSpiderWalkingFrames(this->getDimensions(), scale);
  sprite->scale(sf::Vector2f(scale, scale));
  sprite->setTexture(*player_texture);
  sprite->setTextureRect(*this->walking_frames[0][0]);
}

// Attack with weapon if player has one, otherwise attack with fists
// void Player::attack() {
//   Enemy *enemies_array = this->environment->getEnemies();

//   if (this->current_item != nullptr) {
//     for (int i = 0; i < this->environment->getEnemiesNum(); i++) {
//       if (this->collidingWith(&enemies_array[i])) {
//         enemies_array[i].takeDamage(this->current_item.use(this));
//       }
//     }
//     else if (this->current_item == Null) {
//       for (int i = 0; i < this->environment->getEnemiesNum(); i++) {
//         if (this->collidingWith(enemies_array[i])) {
//           enemies_array[i].takeDamage(this->attack_damage);
//         }
//       }
//     }
//   }
// }


// Pick up item if player is near one
void Player::pickUpItem() {
  this->getNearbyItem();
  // if (this->getNearbyItem() != NULL) {
  //   // this->current_item = item;
  // }
}

// Drop item if player has one
// void Player::dropItem() {
//   if (this->current_item != NULL) {
//     this->current_item = NULL;
//   }
// }

// Get player's score
int Player::getScore() {
  return this->score;
}

// Get nearby item if there is one
void Player::getNearbyItem() {
  Item* items_array = this->environment->getItems();

  for (int i = 0; i < this->environment->getItemsNum(); i++) {
    if (this->collidingWith(&items_array[i])) {
      if (items_array[i].getType() == "potions") {
        items_array[i].use(this);
      }
      //  if (items_array[i].getType() == "weapon") {
      //    // items_array[i].pickUp();
      //    if (this->current_item != NULL) {
      //      // this->current_item.drop();
      //    }
      //    return &items_array[i];
      //  }
      //  if (items_array[i].getType() == "potion") {
      //    items_array[i].use(this);
      //    return NULL;
      //  } 
      //  else {
      //    return NULL;
      //  }
    }
  }
}


void Player::render(sf::RenderWindow *window) {
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

void Player::update() {}
