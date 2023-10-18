#include "../src/Obstacle.h"
#include <criterion/criterion.h>

// Test for Obstacle
Test(obstacle_suite, test_obstacle) {
    Vector position(10, 20);
    string type = "obstacle";
    Vector dimensions(30, 40);

    sf::Texture texture; // Provide a valid texture
    Obstacle obstacle(position, type, dimensions, &texture);

    cr_assert_eq(obstacle.getPosition().getX(), position.getX(), "Position mismatch.");
    cr_assert_eq(obstacle.getDimensions().getX(), dimensions.getX(), "Dimensions mismatch.");
}

//Test update function does nothing
Test(obstacle_suite, test_update) {
    Vector position(10, 20);
    string type = "obstacle";
    Vector dimensions(30, 40);

    sf::Texture texture; // Provide a valid texture
    Obstacle obstacle(position, type, dimensions, &texture);

    obstacle.update();

    cr_assert_eq(obstacle.getPosition().getX(), position.getX(), "Position mismatch.");
    cr_assert_eq(obstacle.getDimensions().getX(), dimensions.getX(), "Dimensions mismatch.");
}
