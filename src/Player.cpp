#include "Player.h"
#include <iostream>
// Default constructor for player does nothing (Environment required)
Player::Player() {}

Player::Player(
  Vector position,
  Vector dimensions,
  string type,
  string movement_animation,
  int movement_speed,
  int health,
  int attack_damage,
  string attack_animation,
  string death_animation,
  Environment* environment,
  sf::Texture* player_texture
) : Entity(
  position,
  dimensions,
  type,
  movement_animation,
  movement_speed,
  health,
  attack_damage,
  attack_animation,
  death_animation
), environment(environment) {
  // Movement
  this->moving_left = false;
  this->moving_right = false;
  this->moving_up = false;
  this->moving_down = false;

  // Loading textures
  // Utility* util = new Utility();
  this->walking_frames = Utility::getPlayerWalkingFrames(this->getDimensions());

  this->current_frames_index = 0;
  this->current_animation_frame = 0;

  this->sprite = new sf::Sprite();
  sprite->setTexture(*player_texture);
  sprite->scale(sf::Vector2f(10, 10));
  sprite->setTextureRect(*this->walking_frames[0][0]);
}

bool Player::canMove() {
  // Loop over all obstacles and check if player is running into them
  for (int i = 0; i < this->environment->getObstaclesNum(); i++) {
    if (this->collidingWith(&(this->environment->getObstacles()[i]))) {
      // If player is colliding with an obstacle, go back to old position.
      return false;
    }
  }
  return true;
}

// Move player up
void Player::moveUp() {
  Vector old_position = this->position;
  this->position.set(this->position.getX(), this->position.getY() - movement_speed);

  if (!this->canMove()) {
    this->position.set(this->position.getX(), old_position.getY());
  }
}

// Move player down
void Player::moveDown() {
  Vector old_position = this->position;
  this->position.set(this->position.getX(), this->position.getY() + movement_speed);

  if (!this->canMove()) {
    this->position.set(this->position.getX(), old_position.getY());

  }
}

// Move player right
void Player::moveRight() {
  Vector old_position = this->position;
  this->position.set(this->position.getX() + movement_speed, this->position.getY());

  if (!this->canMove()) {
    this->position.set(old_position.getX(), this->position.getY());

  }
}

// Move player left
void Player::moveLeft() {
  // Save old position
  Vector old_position = this->position;
  // Move to new position
  this->position.set(this->position.getX() - movement_speed, this->position.getY());

  if (!this->canMove()) {
    this->position.set(old_position.getX(), this->position.getY());

  }
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

// Set whether the player is moving in a given direction or not
// 0 = left
// 1 = right
// 2 = up
// 3 = down
void Player::setMovementDirection(int direction, bool is_moving) {
  switch (direction) {
  case 0:
    this->moving_left = is_moving;
    break;
  case 1:
    this->moving_right = is_moving;
    break;
  case 2:
    this->moving_up = is_moving;
    break;
  case 3:
    this->moving_down = is_moving;
    break;

  default:
    break;
  }
}

// Get whether the player is moving in a current direction or not
int Player::getMovementDirection(int direction) {
  switch (direction) {
  case 0:
    return this->moving_left;
    break;
  case 1:
    return this->moving_right;
    break;
  case 2:
    return this->moving_up;
    break;
  case 3:
    return this->moving_down;
    break;

  default:
    return 0;
    break;
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
