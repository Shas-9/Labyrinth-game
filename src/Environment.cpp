#include "Environment.h"

Environment::Environment(
  sf::Texture* obstacles_texture,
  sf::Texture* potion_texture,
  sf::Texture* iron_spider_texture
) {
  // Generate the paths
  MazeGenerator* maze_generator = new MazeGenerator(obstacles_texture);
  maze_generator->generatePaths();
  Obstacle* map_obstacles = maze_generator->getObstacles();
  this->obstacles_num = maze_generator->getObstaclesNum();
  this->obstacles = map_obstacles;

  // Add the itmes based on the map generated
  // (items must be inside the map and randomly generated)
  this->items_num = 30;
  this->items = new Item[this->items_num];
  for (int i = 0; i < this->items_num; i++) {
    Potion potion = Potion(
      Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS),
      "potion",
      "a health potion",
      30,
      potion_texture
    );

    while (!potion.isInObstacle(this->obstacles, this->obstacles_num)) {
      potion.setPosition(Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS));
    }

    this->items[i] = potion;
  }

  // Add the enemies based on the map generated
  // (enemies must be inside the map and randomly generated)
  this->enemies_num = 100;
  this->enemies = new Enemy[this->enemies_num];
  for (int i = 0; i < this->enemies_num; i++) {
    IronSpider spider = IronSpider(
      Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS),
      this->getObstacles(),
      this->getObstaclesNum(),
      iron_spider_texture
    );

    // If spider was randomly generated in an obstacle, keep randomizing spawn position until a valid location is found
    while (!spider.canMove()) {
      spider.setPosition(Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS));
    }

    this->enemies[i] = spider;
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