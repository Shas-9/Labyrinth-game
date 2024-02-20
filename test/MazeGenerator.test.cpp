#include "../src/MazeGenerator.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>

// Test the generateMazePathConnections method to ensure it creates valid connections.
Test(mazegenerator_suite, test_generate_maze_path_connections) {
  sf::Texture obstacles_texture;
  MazeGenerator maze_generator(&obstacles_texture);

  PointConnections connections = maze_generator.generateMazePathConnections();

  cr_assert(connections.size() > 0, "No connections were generated.");
}

// Test the computeGrid method to verify that it generates valid obstacles.
Test(mazegenerator_suite, test_compute_grid) {
  sf::Texture obstacles_texture;
  MazeGenerator maze_generator(&obstacles_texture);
  PointConnections connections = maze_generator.generateMazePathConnections();

  Obstacle** obstacles = maze_generator.computeGrid(0, 0, MAZE_WIDTH, MAZE_BOX_SIZE, MAZE_BOX_THICKNESS, connections);

  cr_assert_not_null(obstacles, "Obstacles array is not generated.");
}

// Test the getObstacles and getObstaclesNum methods.
Test(mazegenerator_suite, test_get_obstacles_and_obstacles_num) {
  sf::Texture obstacles_texture;
  MazeGenerator maze_generator(&obstacles_texture);

  Obstacle* obstacles = maze_generator.getObstacles();
  int obstacles_num = maze_generator.getObstaclesNum();

  cr_assert_not_null(obstacles, "Obstacles array is not generated.");
  cr_assert(obstacles_num > 0, "Obstacles number is invalid.");
}
