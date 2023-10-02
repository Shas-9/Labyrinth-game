#ifndef ENVIRONMENT_INCLUDE
#define ENVIRONMENT_INCLUDE

#include "Enemy.h"
#include "Item.h"
#include "Obstacle.h"
#include "RenderedObject.h"

class Environment {
 private:
  int obstacles_num;
  int items_num;
  int enemies_num;
  
  Obstacle* obstacles;
  Item* items;
  Enemy* enemies;

 public:
  Environment();
  Obstacle* generatePaths();
  void render();

  Item* getItems();
  Enemy* getEnemies();
  Obstacle* getObstacles();
};

#endif