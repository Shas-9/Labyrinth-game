#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(Vector position, string type, string movement_animation,
             int movement_speed, int health, int attack_damage,
             string attack_animation, string death_animation,
             Obstacle* obstacles, int sight_distance)
    : Entity(position, type, movement_animation, movement_speed, health,
             attack_damage, attack_animation, death_animation),
      obstacles(obstacles),
      sight_distance(sight_distance) {}

void Enemy::takeDamage(int damage) {
  this->health -= damage;
}

void Enemy::update() {}