#include "../src/UI.h"
#include <criterion/criterion.h>
#include <SFML/Graphics.hpp>

// Test for UI
// For the UI class all tests have to be conducted on the screen by the user
// This is because the UI class is responsible for the screen itself
// When the test is run, the user should see the screen pop up

// When the game is finished, everything can be tested through this screen
Test(ui_suite, test_fetch_highscores) {
    // Prepare the UI object
    UI ui(Vector(1920, 1080));
}
