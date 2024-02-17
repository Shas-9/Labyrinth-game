#ifndef IRON_SPIDER_INCLUDE
#define IRON_SPIDER_INCLUDE

#include "Enemy.h"
#include "Utility.h"
#include <ctime>
#include <random>
// #include "Weapon.h"

class IronSpider : public Enemy {
private:

public:
  IronSpider();
  IronSpider(
    Vector position,
    Obstacle* obstacles,
    int obstacles_num
  );

  // void takeDamage(int damage);
};

#endif