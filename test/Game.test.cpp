#include "../src/Game.hpp"
#include <criterion/criterion.h>

// Test for Game
Test(game_suite, test_game) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Test Game Window");
    sf::Event event;
    Vector screen_dimensions(1920, 1080);
    sf::Clock clock;

    Game game(&window, &event, screen_dimensions, &clock);

    cr_assert_not(game.isGameWon(), "Game should not be won at the beginning.");
}

// Test the game pause functionality
// This is done through the screen itself to see if the buttons lead to the correct screens
Test(game_suite, test_game_pause) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Test Game Window");
    sf::Event event;
    Vector screen_dimensions(1920, 1080);
    sf::Clock clock;

    Game game(&window, &event, screen_dimensions, &clock);
}