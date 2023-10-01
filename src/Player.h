#ifndef PLAYER_INCLDUE
#define PLAYER_INCLUDE

#include "Entity.h"
#include "Game.h"
#include "Weapon.h"

class Player : public Entity {
 protected:
  int score;
  Weapon* current_item;
  Game* game;

 public:
  Player(Game* game);
  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();
  void attack();  // If Player has Weapon, use it instead
  void pickUpItem(Item* item);
  void dropItem();
  int getScore();
  Item* getNearbyItem();
  void render();
};

#endif