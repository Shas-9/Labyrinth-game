#include "Environment.h"

// The constructor for the environment, handles the generation of obstacles, enemies, and items all around the map
// Takes in the textures for each object
Environment::Environment(
  sf::Texture* obstacles_texture,
  sf::Texture* potion_texture,
  sf::Texture* iron_spider_texture,
  sf::Texture* cat_texture
) {
  // Generates the paths using the MazeGenerator class
  MazeGenerator* maze_generator = new MazeGenerator(obstacles_texture);
  maze_generator->generatePaths();

  // after generation, point the obstacles pointer to the array of obstacles generated
  Obstacle* map_obstacles = maze_generator->getObstacles();
  this->obstacles_num = maze_generator->getObstaclesNum();
  this->obstacles = map_obstacles;

  // Add the items based on the map generated
  this->items_num = 31;
  this->items = new Item[this->items_num];

  // Add health items
  // (items must be inside the map and randomly generated && not inside any obstacles)
  for (int i = 0; i < this->items_num; i++) {
    // Create a potion object at a random location
    Potion potion = Potion(
      Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS),
      potion_texture
    );

    // Check if the item is in an obstacle
    while (!potion.isInObstacle(this->obstacles, this->obstacles_num)) {
      // Keep randomizing the location until a position that satisfies that the
      // item is not inside an obstacle is met
      potion.setPosition(Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS));
    }

    // Add the potion to the array of items
    this->items[i] = potion;
  }

  // Add the enemies based on the map generated
  this->enemies_num = 100;
  this->enemies = new Enemy[this->enemies_num];

  // Add enemies
  // (enemies must be inside the map and randomly generated)
  for (int i = 0; i < this->enemies_num; i++) {
    // Create an Iron Spider enemy at a random location
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

    // Add the spider to the the array of enemies
    this->enemies[i] = spider;
  }

  // Set the first item to be the cat item, which the player needs to find
  // Always positioned at the bottom right corner of the map
  this->items[0] = Cat(Vector(MAP_BOUNDS - MAZE_BOX_THICKNESS, MAP_BOUNDS - MAZE_BOX_THICKNESS), cat_texture);
}

// Remove an item from the map (after the player picked it up)
void Environment::removeItem(int index) {
  // Checks if the index given is valid
  if (index < this->items_num) {
    // Create new memory with less size to store the items
    Item* new_items_array = new Item[this->items_num - 1];
    // Temp pointer to the old memory
    Item* temp = this->items;

    // Loop through and copy all items from old array to new
    // except the removed item
    int index_reached = 0;
    for (int i = 0; i < this->items_num; i++) {
      if (i == index) {
        index_reached = 1;
      } else {
        new_items_array[i - index_reached] = this->items[i];
      }
    }

    // Decrease items_num value and set new array
    this->items_num--;
    this->items = new_items_array;

    // Free memory
    delete[] temp;
  }
}

// Get the pointer to the obstacles array
Obstacle* Environment::getObstacles() {
  return this->obstacles;
}

// Get the pointer to the items array
Item* Environment::getItems() {
  return this->items;
}

// Get the pointer to the enemies array
Enemy* Environment::getEnemies() {
  return this->enemies;
}

// Get the number of obstacles in the environment
int Environment::getObstaclesNum() {
  return this->obstacles_num;
}

// Get the number of items in the environment
int Environment::getItemsNum() {
  return this->items_num;
}

// Get the number of enemies in the environment
int Environment::getEnemiesNum() {
  return this->enemies_num;
}

// Free the memory in environment class
Environment::~Environment() {
  delete[] this->items;
  delete[] this->enemies;
  delete[] this->obstacles;
}