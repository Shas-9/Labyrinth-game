#include "../src/Player.hpp"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <SFML/Graphics.hpp>
#include "../src/Environment.hpp"

// Test the default constructor for Player
Test(player_suite, test_constructor_default) {
  Player player;

  cr_assert(player.getScore() == 0, "Default Constructor: Score is not 0.");
}

// Test the parameterized constructor for Player
Test(player_suite, test_constructor_parameterized) {
  Vector position(10, 15);
  Vector dimensions(20, 30);
  string type = "TestType";
  int movement_speed = 5;
  int health = 100;
  int attack_damage = 10;
  sf::Texture* texture;
  Environment environment(texture, texture, texture, texture);
  sf::Texture player_texture;

  Player player(position, dimensions, type, movement_speed, health, attack_damage, &environment, &player_texture);

  // Check if default score is 0
  cr_assert(player.getScore() == 0, "Parameterized Constructor: Score is not 0.");
}