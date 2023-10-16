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

void Enemy::update() {}