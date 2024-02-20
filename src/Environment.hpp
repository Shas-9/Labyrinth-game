#ifndef ENVIRONMENT_INCLUDE
#define ENVIRONMENT_INCLUDE

#include <SFML/Graphics.hpp>

#include "Enemy.hpp"
#include "IronSpider.hpp"
#include "Item.hpp"
#include "Potion.hpp"
#include "Block.hpp"
#include "Renderable.hpp"
#include "MazeGenerator.hpp"
#include "Cat.hpp"

// Data Structures
#include <vector>
#include <unordered_set>

// Namespaces
using std::vector;
using std::unordered_set;

// Environment class: Handles the generation, allocation, storage, and management of all objects in the 
// surroundings of the player, including Obstacles/Walls, Enemies, items.
class Environment {
private:
  vector<Block> blocks;
  vector<Item> items;
  vector<Enemy> enemies;
  Cat cat;

public:
  Environment();

  void removeItem(int index);

  Cat getCat();
  vector<Enemy>& Environment::getEnemies();
  vector<Item>& Environment::getItems();
  vector<Block>& Environment::getBlocks();
};

#endif