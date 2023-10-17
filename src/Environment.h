#ifndef ENVIRONMENT_INCLUDE
#define ENVIRONMENT_INCLUDE

#include <SFML/Graphics.hpp>

#include "Enemy.h"
#include "IronSpider.h"
#include "Item.h"
#include "Potion.h"
#include "Obstacle.h"
#include "RenderedObject.h"
#include "MazeGenerator.h"

class Environment {
private:
  int obstacles_num;
  int items_num;
  int enemies_num;

  Obstacle* obstacles;
  Item* items;
  Enemy* enemies;

  sf::RenderWindow *window_ptr;

public:
  Environment();
  Environment(
    sf::Texture* obstacles_texture,
    sf::Texture* potion_texture,
    sf::Texture* iron_spider_textures
  );
  void render(sf::RenderWindow *window_ptr);

  int getObstaclesNum();
  int getItemsNum();
  int getEnemiesNum();

  Item* getItems();
  Enemy* getEnemies();
  Obstacle* getObstacles();
};

#endif