#ifndef ENEMY_INCLUDE
#define ENEMY_INCLUDE

#include "Entity.h"
#include "Obstacle.h"
#include "Weapon.h"

class Enemy : public Entity {
 protected:
  Obstacle* obstacles;
  int sight_distance;

 public:
  Enemy();
  Enemy(Vector position, string type, string movement_animation,
        int movement_speed, int health, int attack_damage,
        string attack_animation, string death_animation,
        Obstacle* obstacles, int sight_distance);
  void trackPlayer();
  void update();

  virtual void render();
};

#endif