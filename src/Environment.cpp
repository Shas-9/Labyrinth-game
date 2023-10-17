#include "Environment.h"

Environment::Environment(
  sf::Texture* obstacles_texture,
  sf::Texture* items_textures,
  sf::Texture* enemies_textures
) {
  // Generate the paths
  MazeGenerator* maze_generator = new MazeGenerator(obstacles_texture);
  maze_generator->generatePaths();
  Obstacle* map_obstacles = maze_generator->getObstacles();
  this->obstacles_num = maze_generator->getObstaclesNum();
  this->obstacles = map_obstacles;

  // Add the itmes based on the map generated
  // (items must be inside the map and randomly generated)
  this->items = new Item[100];
  int i = 0;
  while (i < 100) {
    // Make a randomly generated item within the borders of the map
    // Logic here

    bool isItemInMap = false;
    // Check if item is in map...
    // Logic here

    if (isItemInMap) {
      // Item isn't out of border!! It can be added :)
      // Add item
      // Logic here

      // Move on to randomly generate the next item
    }
    i++;
  }

  // Add the enemies based on the map generated
  // (enemies must be inside the map and randomly generated)
  this->enemies_num = 100;
  this->enemies = new Enemy[this->enemies_num];
  for (int i = 0; i < this->enemies_num; i++) {
    IronSpider spider = IronSpider(
      Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS),
      2,
      100,
      10,
      this->getObstacles(),
      this->getObstaclesNum(),
      30,
      enemies_textures
    );

    // If spider was randomly generated in an obstacle, keep randomizing spawn position until a valid location is found
    while (!spider.canMove()) {
      spider.setPosition(Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS));
    }

    this->enemies[i] = spider;
  }

  int k = 0;
  while (k < 100) {
    // Make a randomly generated enemy within the borders of the map
    // Logic here

    bool isEnemyInMap = false;
    // Check if enemy is in map...
    // Logic here

    if (isEnemyInMap) {
      // Enemy isn't out of border!! It can be added :)
      // Add enemy
      // Logic here

      // Move on to randomly generate the next enemy
    }
    k++;
  }
}


Obstacle* Environment::getObstacles() {
  return this->obstacles;
}

Item* Environment::getItems() {
  return this->items;
}

Enemy* Environment::getEnemies() {
  return this->enemies;
}

int Environment::getObstaclesNum() {
  return this->obstacles_num;
}

int Environment::getItemsNum() {
  return this->items_num;
}

int Environment::getEnemiesNum() {
  return this->enemies_num;
}