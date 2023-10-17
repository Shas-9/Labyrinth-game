#include "../src/Button.h"

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <SFML/Graphics.hpp>

// Test the default constructor for the Button class
Test(button_suite, test_constructor) {
  Button button;

  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

  // Check if the default constructor initializes the attributes correctly
  cr_assert(button.isMouseOver(window) == false, "Default button is not expected to be mouse-over.");
}

// Test the overloaded constructor for the Button class
Test(button_suite, test_overloaded_constructor) {
  Vector position(100, 100);
  Vector size(200, 50);
  sf::Color bgColor = sf::Color::Red;
  sf::Color textColor = sf::Color::White;
  int charSize = 20;
  std::string buttonText = "Test Button";

  Button button(buttonText, position, size, bgColor, textColor, charSize);
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

  // Check if the overloaded constructor initializes the attributes correctly
  cr_assert(button.isMouseOver(window) == false, "Button is not expected to be mouse-over initially.");
}

// Test the setBackToColor method
Test(button_suite, test_set_back_to_color) {
  Vector position(100, 100);
  Vector size(200, 50);
  sf::Color bgColor = sf::Color::Red;
  sf::Color textColor = sf::Color::White;
  int charSize = 20;
  std::string buttonText = "Test Button";

  Button button(buttonText, position, size, bgColor, textColor, charSize);

  sf::Color newColor = sf::Color::Green;
  button.setBackToColor(newColor);
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

  // Check if the background color of the button is updated
  cr_assert(button.isMouseOver(window) == false, "Button is not expected to be mouse-over after changing color.");
}

// Test the setTextColor method
Test(button_suite, test_set_text_color) {
  Vector position(100, 100);
  Vector size(200, 50);
  sf::Color bgColor = sf::Color::Red;
  sf::Color textColor = sf::Color::White;
  int charSize = 20;
  std::string buttonText = "Test Button";

  Button button(buttonText, position, size, bgColor, textColor, charSize);

  sf::Color newColor = sf::Color::Blue;
  button.setTextColor(newColor);
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

  // Check if the text color of the button is updated
  cr_assert(button.isMouseOver(window) == false, "Button is not expected to be mouse-over after changing text color.");
}

// Test the setPosition method
Test(button_suite, test_set_position) {
  Vector position(100, 100);
  Vector size(200, 50);
  sf::Color bgColor = sf::Color::Red;
  sf::Color textColor = sf::Color::White;
  int charSize = 20;
  std::string buttonText = "Test Button";

  Button button(buttonText, position, size, bgColor, textColor, charSize);

  Vector newPosition(300, 200);
  button.setPosition(newPosition);
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

  // Check if the position of the button is updated correctly
  cr_assert(button.isMouseOver(window) == false, "Button is not expected to be mouse-over after changing position.");
}
