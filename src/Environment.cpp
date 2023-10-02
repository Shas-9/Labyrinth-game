#include "Environment.h"

Environment::Environment() {
  // Generate the paths
  Obstacle* map_obstacles = this->generatePaths();
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
      i++;
    }
  }

  // Add the enemies based on the map generated
  // (enemies must be inside the map and randomly generated)
  this->enemies = new Enemy[100];
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
      k++;
    }
  }
}

// Generates paths for the map and returns the corresponding obstacles array.
// Sets the obstacles_num attribute at the end of the function so that
// the length of the return array is known.
Obstacle* Environment::generatePaths() {
  // TEMPORARY CODE, THE REAL FUNCTIONALITY MUST BE IMPLEMENTED LATER
  Obstacle* temporary = new Obstacle();
  this->obstacles_num = 1;
  return temporary;
}