#include "../src/Obstacle.hpp"
#include <criterion/criterion.h>

// Test for Obstacle
Test(obstacle_suite, test_obstacle) {
    Vector position(10, 20);
    string type = "obstacle";
    Vector dimensions(30, 40);

    sf::Texture texture;
    
    Obstacle obstacle(position, type, dimensions, &texture);

    // Asseertions to test if the obstacle is created correctly
    cr_assert_eq(obstacle.getPosition().getX(), position.getX(), "Position mismatch.");
    cr_assert_eq(obstacle.getDimensions().getX(), dimensions.getX(), "Dimensions mismatch.");
}

//Test update function does nothing
Test(obstacle_suite, test_update) {
    Vector position(10, 20);
    string type = "obstacle";
    Vector dimensions(30, 40);

    sf::Texture texture;
    Obstacle obstacle(position, type, dimensions, &texture);

    obstacle.update();


    // Asseertions to test whether the update function changes anything
    cr_assert_eq(obstacle.getPosition().getX(), position.getX(), "Position mismatch.");
    cr_assert_eq(obstacle.getDimensions().getX(), dimensions.getX(), "Dimensions mismatch.");
}
