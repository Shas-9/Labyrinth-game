#ifndef UI_INCLUDE
#define UI_INCLUDE

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "../src/Vector.h"

class CamTesting {
public:
  CamTesting() { CamTesting(Vector(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)); }
  CamTesting(int width, int height) { CamTesting(Vector(width, height)); }

  CamTesting(Vector screen_dimensions) {
    ScreenManager::getInstance().setScreenDimensions(screen_dimensions);

    sf::RenderWindow window(sf::VideoMode(screen_dimensions.getX(), screen_dimensions.getY()), "CatQuest");
    ScreenManager::getInstance().setWindowObject(&window);
  }

};

#endif