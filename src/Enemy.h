#ifndef ENEMY_INCLUDE
#define ENEMY_INCLUDE

#include "Entity.h"
#include "Obstacle.h"

// Enemy class: Base class for all enemy classes and handles the logic of moving across the map
class Enemy : public Entity {

public:
      Enemy();
      Enemy(
            Vector position,
            Vector dimensions,
            string type,
            int movement_speed,
            int health,
            int attack_damage,
            Obstacle* obstacles,
            int obstacles_num,
            int sight_distance
      );

      void update();
};

#endif