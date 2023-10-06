#include "Entity.h"

Entity::Entity() {}

Entity::Entity(Vector position, string type, string movement_animation,
               int movement_speed, int health, int attack_damage,
               string attack_animation, string death_animation)
    : RenderedObject(position, type),
      movement_animation(movement_animation),
      movement_speed(movement_speed),
      health(health),
      attack_damage(attack_damage),
      attack_animation(attack_animation),
      death_animation(death_animation) {
  // Create an entity
}

void Entity::changePosition(Vector position) {
  this->position.setPosition(position.getXPosition(), position.getYPosition());
}

void Entity::update() {}