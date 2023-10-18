#include "../src/Game.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <SFML/Graphics.hpp>
#include "../src/Environment.h"
#include <SFML/System/Clock.hpp>

Test(game_suite, test_constructor_default) {
    // Test the default constructor
    sf::RenderWindow window;
    sf::Texture* texture;
    Environment environment(texture, texture, texture, texture);
    sf::Clock clock;

    Game game(&window, nullptr, Vector(800, 600), &clock);

    cr_assert(game.isGameWon() == false, "Default Constructor: Game should not be won.");
    // Add more assertions for other default values if necessary.
}

// Test(game_suite, test_pause_and_resume) {
//     // Test the pause and resume functionality
//     sf::RenderWindow window;
//     Environment environment;
//     sf::Clock clock;

//     Game game(&window, nullptr, Vector(800, 600), &clock);

//     // Simulate pausing the game
//     game.pause();
//     cr_assert(game.isGamePaused() == true, "Game should be paused.");

//     // Simulate resuming the game
//     game.resume();
//     cr_assert(game.isGamePaused() == false, "Game should be resumed.");
// }
