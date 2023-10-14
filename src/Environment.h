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

  Obstacle* generatePaths();

 public:
  Environment();
  void render();

  int getObstaclesNum();
  int getItemsNum();
  int getEnemiesNum();

  Item* getItems();
  Enemy* getEnemies();
  Obstacle* getObstacles();
};

#endif