#include "../src/Item.h"
#include <criterion/criterion.h>
#include <SFML/Graphics.hpp>

Test(item_suite, test_constructor) {
    // Test the constructor
    Vector position(100, 100);
    Vector dimensions(30, 30);
    Item item(position, dimensions, "health", "Health Potion");

    cr_assert_eq(item.getType(), "health", "Item should have type 'health'");
}

Test(item_suite, test_obstacle_check) {
    // Test the obstacle check method
    Vector position(100, 100);
    Vector dimensions(30, 30);
    Obstacle obstacles[1];
    int obstacles_num = 1;
    Item item(position, dimensions, "health", "Health Potion");

    bool result = item.isInObstacle(obstacles, obstacles_num);
    cr_assert(result, "Item should not be in an obstacle");

    sf::Texture texture;

    // Simulate item inside an obstacle
    obstacles[0] = Obstacle(Vector(90, 90), "potion", Vector(40, 40), &texture);
    result = item.isInObstacle(obstacles, obstacles_num);
    cr_assert_not(result, "Item should be inside an obstacle");
}
