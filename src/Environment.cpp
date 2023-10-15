#include "Environment.h"

// #include <unistd.h>

#include <ctime>
#include <iostream>
#include <random>

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

  // std::cout << "HELLOOOOO" << std::endl;

  // /* initialize random seed: */
  // srand(time(NULL));

  // int** grid = new int*[100];

  // for (int i = 0; i < 100; i++) {
  //   grid[i] = new int[100];
  //   for (int k = 0; k < 100; k++) {
  //     grid[i][k] = 0;
  //   }
  // }

  // for (int i = 0; i < 100; i++) {
  //   for (int k = 0; k < 100; k++) {
  //     std::cout << grid[i][k] << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // // The current direction of the algorithm
  // // 0 = right
  // // 1 = left
  // // 2 = top
  // // 3 = bottom
  // int current_direction = 0;
  // bool directions[4] = {0};
  // bool can_move = true;

  // int position_x = 3;
  // int position_y = 50;

  // // while (can_move) {
  // //   sleep(1);

  // //   for (int i = 0; i < 100; i++) {
  // //     for (int k = 0; k < 100; k++) {
  // //       std::cout << grid[i][k] << " ";
  // //     }
  // //     std::cout << std::endl;
  // //   }

  // //   directions[0] = false;
  // //   directions[1] = false;
  // //   directions[2] = false;
  // //   directions[3] = false;

  // //   // move
  // //   int new_direction = rand() % 3 + 1;

  // //   // Checks if can move at all
  // //   if (position_x + 2 < 100 || position_x - 2 > 0 || position_y + 2 < 100 ||
  // //       position_y - 2 > 0) {
  // //     // Check if can move to the right
  // //     if (position_x + 2 < 100 && grid[position_y][position_x + 2] != 1 &&
  // //         current_direction != 1) {
  // //       directions[0] = true;
  // //     }
  // //     if (position_x - 2 > 0 && grid[position_y][position_x - 2] != 1 &&
  // //         current_direction != 0) {
  // //       directions[1] = true;
  // //     }
  // //     if (position_y - 2 > 0 && grid[position_y - 2][position_x] != 1 &&
  // //         current_direction != 3) {
  // //       directions[2] = true;
  // //     }
  // //     if (position_y + 2 < 100 && grid[position_y + 3][position_x] != 1 &&
  // //         current_direction != 2) {
  // //       directions[3] = true;
  // //     }

  // //     bool local_can_move = false;

  // //     for (int i = 0; i < 3; i++) {
  // //       if (directions[i]) local_can_move = true;
  // //     }

  // //     can_move = local_can_move;

  // //     if (directions[new_direction]) {
  // //       if (new_direction == 0) position_x + 1;
  // //       if (new_direction == 1) position_x - 1;
  // //       if (new_direction == 2) position_y - 1;
  // //       if (new_direction == 3) position_y + 1;
  // //       grid[position_y][position_x] = 1;
  // //     }

  // //   } else
  // //     can_move = false;
  // // }

  // // Print out the grid
  // for (int i = 0; i < 100; i++) {
  //   for (int k = 0; k < 100; k++) {
  //     std::cout << grid[i][k] << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // TEMPORARY CODE, THE REAL FUNCTIONALITY MUST BE IMPLEMENTED LATER
  Obstacle* temporary = new Obstacle();
  this->obstacles_num = 1;
  return temporary;
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