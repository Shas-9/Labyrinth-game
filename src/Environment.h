#ifndef ENVIRONMENT_INCLUDE
#define ENVIRONMENT_INCLUDE

#include <SFML/Graphics.hpp>

#include "Enemy.h"
#include "IronSpider.h"
#include "Item.h"
#include "Potion.h"
#include "FastPotion.h"
#include "Obstacle.h"
#include "RenderedObject.h"
#include "MazeGenerator.h"
#include "Cat.h"

// Environment class: Handles the generation, allocation, storage, and management of all objects in the 
// surroundings of the player, including Obstacles/Walls, Enemies, items.
class Environment {
private:
  int obstacles_num;
  int items_num;
  int enemies_num;

  Obstacle* obstacles;
  Item* items;
  Enemy* enemies;
  Cat cat;

  sf::RenderWindow *window_ptr;

public:
  Environment(
    sf::Texture* obstacles_texture,
    sf::Texture* potion_texture,
    sf::Texture* iron_spider_texture,
    sf::Texture* cat_texture
  );
  Environment(
    sf::Texture* obstacles_texture,
    sf::Texture* potion_texture,
    sf::Texture* iron_spider_texture,
    sf::Texture* cat_texture,
    sf::Texture* fast_texture
  );
  ~Environment();

  void removeItem(int index);

  int getObstaclesNum();
  int getItemsNum();
  int getEnemiesNum();

  Item* getItems();
  Cat getCat();
  Enemy* getEnemies();
  Obstacle* getObstacles();
};

#endif