#include "Entity.h"

Entity::Entity() {}

// The constructor for the object
Entity::Entity(
  Vector position,
  Vector dimensions,
  string type,
  string movement_animation,
  int movement_speed,
  int health,
  int attack_damage,
  string attack_animation,
  string death_animation
) : RenderedObject(position, dimensions, type),
movement_animation(movement_animation),
movement_speed(movement_speed),
health(health),
attack_damage(attack_damage),
attack_animation(attack_animation),
death_animation(death_animation) {
  this->max_health = 100;
  this->health = this->max_health;
}

void Entity::changePosition(Vector position) {
  this->position.set(position.getX(), position.getY());
}

int Entity::getHealth() {
  return this->health;
}

int Entity::getMaxHealth() {
  return this->max_health;
}

void Entity::setHealth(int health) {
  this->health = health;
}

void Entity::setMaxHealth(int max_health) {
  this->max_health = max_health;
}