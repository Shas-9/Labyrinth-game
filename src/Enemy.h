#ifndef ENEMY_INCLUDE
#define ENEMY_INCLUDE

#include "Entity.h"
#include "Obstacle.h"
// #include "Weapon.h"

class Enemy : public Entity {
protected:
      int sight_distance;

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
      // void trackPlayer();
      void update() override;

      void takeDamage(int damage);
};

#endif