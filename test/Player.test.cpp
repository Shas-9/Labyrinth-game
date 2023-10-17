#include "../src/Player.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <SFML/Graphics.hpp>
#include "../src/Environment.h"

// Test the default constructor for Player
Test(player_suite, test_constructor_default) {
  Player player;

  cr_assert(player.getScore() == 0, "Default Constructor: Score is not 0.");
  // You can add more assertions for other default values if necessary.
}

// Test the parameterized constructor for Player
Test(player_suite, test_constructor_parameterized) {
  Vector position(10, 15);
  Vector dimensions(20, 30);
  string type = "TestType";
  int movement_speed = 5;
  int health = 100;
  int attack_damage = 10;
  Environment environment;
  sf::Texture player_texture;

  Player player(position, dimensions, type, movement_speed, health, attack_damage, &environment, &player_texture);

  cr_assert(player.getScore() == 0, "Parameterized Constructor: Score is not 0.");
  // Add more assertions for other attributes if needed.
}