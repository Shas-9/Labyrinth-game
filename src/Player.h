#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

#include "Entity.h"
#include "Environment.h"
#include "Weapon.h"

class Player : public Entity {
 protected:
  int score;
  Weapon* current_item;
  Environment* environment;

 public:
  Player();
  Player(Vector position, string type, string movement_animation,
         int movement_speed, int health, int attack_damage,
         string attack_animation, string death_animation,
         Environment* environment);
  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();
  void attack();  // If Player has Weapon, use it instead
  void pickUpItem(Item* item);
  void dropItem();
  int getScore();
  Item* getNearbyItem();
  void render(sf::RenderWindow &window);
};

#endif