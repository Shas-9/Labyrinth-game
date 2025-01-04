#include "UI.h"

#include "global.h"
#include "ScreenFactory.h"
#include "singleton/ScreenManager.h"

#define CURRENT_SCREEN ScreenManager::getInstance().screens[ScreenManager::getInstance().current_screen_i]

// Default constructor
UI::UI() { UI(Vector(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)); }

// Overloaded constructor with width and height
UI::UI(int width, int height) { UI(Vector(width, height)); }

// Overloaded constructor with Vector
UI::UI(Vector screen_dimensions) {
  ScreenManager::getInstance().setScreenDimensions(screen_dimensions);

  sf::RenderWindow window(sf::VideoMode(screen_dimensions.getX(), screen_dimensions.getY()), "CatQuest");
  ScreenManager::getInstance().setWindowObject(&window);

  ScreenManager::getInstance().screens.push_back(ScreenFactory::mainScreen());
  ScreenManager::getInstance().screens.push_back(ScreenFactory::tutorialScreen());
  ScreenManager::getInstance().screens.push_back(ScreenFactory::highscoresScreen());
  ScreenManager::getInstance().screens.push_back(ScreenFactory::gameScreen());
  ScreenManager::getInstance().screens.push_back(ScreenFactory::pauseScreen());
  ScreenManager::getInstance().screens.push_back(ScreenFactory::losingScreen());
  ScreenManager::getInstance().screens.push_back(ScreenFactory::winningScreen());
  ScreenManager::getInstance().screens.push_back(ScreenFactory::highscoreWinningScreen());
  
  sf::Event event;

  // Screen loop
  while (window.isOpen()) {
    // Update the current screen
    while (window.pollEvent(event)) CURRENT_SCREEN.update(event);

    // Render the current screen
    window.clear();
    if (CURRENT_SCREEN.screen_name == "game_screen") Game::getInstance().update();
    if (CURRENT_SCREEN.screen_name == "game_screen") Game::getInstance().render();
    CURRENT_SCREEN.render();
    window.display();
  }
}