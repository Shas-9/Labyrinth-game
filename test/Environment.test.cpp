#include "../src/Environment.h"

#include <criterion/criterion.h>

// Test the constructor of the Environment class to ensure that
// it correctly initializes the obstacles, items, and enemies.
Test(environment_suite, test_constructor) {
  sf::Texture obstacles_texture;
  sf::Texture potion_texture;
  sf::Texture iron_spider_texture;

  Environment environment(&obstacles_texture, &potion_texture, &iron_spider_texture);

  // Check that the number of obstacles, items, and enemies are greater than 0
  cr_assert(environment.getObstaclesNum() > 0, "Obstacles not initialized.");
  cr_assert(environment.getItemsNum() > 0, "Items not initialized.");
  cr_assert(environment.getEnemiesNum() > 0, "Enemies not initialized.");
}

// Test that the getObstacles method returns a valid pointer.
Test(environment_suite, test_get_obstacles) {
  sf::Texture obstacles_texture;
  sf::Texture potion_texture;
  sf::Texture iron_spider_texture;

  Environment environment(&obstacles_texture, &potion_texture, &iron_spider_texture);

  Obstacle* obstacles = environment.getObstacles();

  // Check that the returned pointer is not null
  cr_assert_not_null(obstacles, "Obstacles pointer is null.");
}

// Test that the getItems method returns a valid pointer.
Test(environment_suite, test_get_items) {
  sf::Texture obstacles_texture;
  sf::Texture potion_texture;
  sf::Texture iron_spider_texture;

  Environment environment(&obstacles_texture, &potion_texture, &iron_spider_texture);

  Item* items = environment.getItems();

  // Check that the returned pointer is not null
  cr_assert_not_null(items, "Items pointer is null.");
}

// Test that the getEnemies method returns a valid pointer.
Test(environment_suite, test_get_enemies) {
  sf::Texture obstacles_texture;
  sf::Texture potion_texture;
  sf::Texture iron_spider_texture;

  Environment environment(&obstacles_texture, &potion_texture, &iron_spider_texture);

  Enemy* enemies = environment.getEnemies();

  // Check that the returned pointer is not null
  cr_assert_not_null(enemies, "Enemies pointer is null.");
}

// Test the getter methods for the number of obstacles, items, and enemies.
Test(environment_suite, test_get_counts) {
  sf::Texture obstacles_texture;
  sf::Texture potion_texture;
  sf::Texture iron_spider_texture;

  Environment environment(&obstacles_texture, &potion_texture, &iron_spider_texture);

  // Check that the number of obstacles, items, and enemies are greater than or equal to 0
  cr_assert(environment.getObstaclesNum() >= 0, "Invalid number of obstacles.");
  cr_assert(environment.getItemsNum() >= 0, "Invalid number of items.");
  cr_assert(environment.getEnemiesNum() >= 0, "Invalid number of enemies.");
}
