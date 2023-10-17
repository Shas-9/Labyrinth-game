#include "../src/Item.h"
#include <criterion/criterion.h>
#include <SFML/Graphics.hpp>

Test(item_suite, test_constructor) {
    // Test the constructor
    Vector position(100, 100);
    Vector dimensions(30, 30);
    Item item(position, dimensions, "health", "Health Potion");

    cr_assert_eq(item.getType(), "health", "Item should have type 'health'");
    cr_assert_eq(item.getDescription(), "Health Potion", "Item should have the correct description");
    // Add more assertions for other constructor parameters if necessary.
}

Test(item_suite, test_obstacle_check) {
    // Test the obstacle check method
    Vector position(100, 100);
    Vector dimensions(30, 30);
    Obstacle obstacles[1]; // You might need to create a real Obstacle object
    int obstacles_num = 1;
    Item item(position, dimensions, "health", "Health Potion");

    bool result = item.isInObstacle(obstacles, obstacles_num);
    cr_assert(result, "Item should not be in an obstacle");

    // Simulate item inside an obstacle
    obstacles[0] = Obstacle(Vector(90, 90), Vector(40, 40), "obstacle");
    result = item.isInObstacle(obstacles, obstacles_num);
    cr_assert_not(result, "Item should be inside an obstacle");
}