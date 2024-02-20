#include "Environment.hpp"

// The constructor for the environment, handles the generation of obstacles, enemies, and items all around the map
// Takes in the textures for each object
Environment::Environment() {
  // Generates the paths using the MazeGenerator class
  MazeGenerator* maze_generator = new MazeGenerator();
  maze_generator->generatePaths();

  // after generation, point the obstacles pointer to the array of obstacles generated
  this->blocks = maze_generator->getBlocks();

  // generate the map

  // Add the items based on the map generated

  // Add health items
  // (items must be inside the map and randomly generated && not inside any obstacles)
  for (int i = 0; i < 30; i++) {
    // Create a potion object at a random location
    Potion potion = Potion(Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS));

    // Check if the item is in an obstacle
    while (!potion.isInObstacle(this->obstacles, this->obstacles_num)) {
      // Keep randomizing the location until a position that satisfies that the
      // item is not inside an obstacle is met
      potion.setPos(Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS));
    }

    // Add the potion to the array of items
    this->items.push_back(potion);
  }

  // Add the enemies based on the map generated

  // Add enemies
  // (enemies must be inside the map and randomly generated)
  for (int i = 0; i < 100; i++) {
    // Create an Iron Spider enemy at a random location
    IronSpider spider = IronSpider(
      Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS),
      this->getObstacles(),
      this->getObstaclesNum()
    );

    // If spider was randomly generated in an obstacle, keep randomizing spawn position until a valid location is found
    while (!spider.canMove()) {
      spider.setPos(Vector(rand() % MAP_BOUNDS, rand() % MAP_BOUNDS));
    }

    // Add the spider to the the array of enemies
    this->enemies.push_back(spider);
  }

  // Set the first item to be the cat item, which the player needs to find
  // Always positioned at the bottom right corner of the map
  this->cat = Cat(Vector(MAP_BOUNDS - MAZE_BOX_THICKNESS, MAP_BOUNDS - MAZE_BOX_THICKNESS));
}

// Remove an item from the map (after the player picked it up)
void Environment::removeItem(int index) {
  // Checks if the index given is valid
  if (index < this->items.size()) {
    // remove it from the vector
    this->items.erase(this->items.begin() + index);
  }
}

// Get a reference to the blocks array
vector<Block>& Environment::getBlocks() {
  return this->blocks;
}

// Get a reference to the items array
vector<Item>& Environment::getItems() {
  return this->items;
}

// Get the pointer to the items array
Cat Environment::getCat() {
  return this->cat;
}

// Get the pointer to the enemies array
vector<Enemy>& Environment::getEnemies() {
  return this->enemies;
}