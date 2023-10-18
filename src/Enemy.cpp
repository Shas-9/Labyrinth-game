#include "Enemy.h"

// Empty default constructor
Enemy::Enemy() {}

// Constructor that sets the properties of the enemy
Enemy::Enemy(
  Vector position,
  Vector dimensions,
  string type,
  int movement_speed,
  int health,
  int attack_damage,
  Obstacle* obstacles,
  int obstacles_num,
  int sight_distance
) : Entity(
  position,
  dimensions,
  type,
  movement_speed,
  health,
  attack_damage,
  obstacles,
  obstacles_num
) {}

// Update function that handles the random movement in the enemy object
void Enemy::update() {
  // With every tick in the game, this function is fired

  // A random number is generated between 0 and 5000
  int random_int = rand() % 5000;

  // If the number is 7 or smaller (0.14% chance)
  // The enemy updates its current movement state
  if (random_int <= 7) {
    // random_int = 0: Start moving left
    // random_int = 1: Start moving right
    // random_int = 2: Start moving up
    // random_int = 3: Start moving down
    // random_int >= 4: Stop moving

    // Left
    if (random_int == 0) {
      this->setMovementDirection(0, true);
      this->setMovementDirection(1, false);
      this->setMovementDirection(2, false);
      this->setMovementDirection(3, false);
    }
    // right
    if (random_int == 1) {
      this->setMovementDirection(0, false);
      this->setMovementDirection(1, true);
      this->setMovementDirection(2, false);
      this->setMovementDirection(3, false);
    }
    // up
    if (random_int == 2) {
      this->setMovementDirection(0, false);
      this->setMovementDirection(1, false);
      this->setMovementDirection(2, true);
      this->setMovementDirection(3, false);
    }
    // down
    if (random_int == 3) {
      this->setMovementDirection(0, false);
      this->setMovementDirection(1, false);
      this->setMovementDirection(2, false);
      this->setMovementDirection(3, true);
    }
    // no movement
    if (random_int >= 4) {
      this->setMovementDirection(0, false);
      this->setMovementDirection(1, false);
      this->setMovementDirection(2, false);
      this->setMovementDirection(3, false);
    }
  }
}
