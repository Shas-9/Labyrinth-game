#include "Enemy.h"

Enemy::Enemy() {}

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
), sight_distance(sight_distance) {}

void Enemy::takeDamage(int damage) {
  this->health -= damage;
}

void Enemy::update() {
  int random_int = rand() % 5000;
  if (random_int <= 7) {
    if (random_int == 0) {
      this->setMovementDirection(0, true);
      this->setMovementDirection(1, false);
      this->setMovementDirection(2, false);
      this->setMovementDirection(3, false);
    }
    if (random_int == 1) {
      this->setMovementDirection(0, false);
      this->setMovementDirection(1, true);
      this->setMovementDirection(2, false);
      this->setMovementDirection(3, false);
    }
    if (random_int == 2) {
      this->setMovementDirection(0, false);
      this->setMovementDirection(1, false);
      this->setMovementDirection(2, true);
      this->setMovementDirection(3, false);
    }
    if (random_int == 3) {
      this->setMovementDirection(0, false);
      this->setMovementDirection(1, false);
      this->setMovementDirection(2, false);
      this->setMovementDirection(3, true);
    }
    if (random_int >= 4) {
      this->setMovementDirection(0, false);
      this->setMovementDirection(1, false);
      this->setMovementDirection(2, false);
      this->setMovementDirection(3, false);
    }
  }
}
