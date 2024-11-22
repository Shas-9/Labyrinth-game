#include "ScreenManager.h"

ScreenManager::ScreenManager() {
  this->current_screen_i = 0;
}

void ScreenManager::switchScreen(std::string screen_name) {
  for (int i = 0; i < this->screens.size(); i++) {
    Screen &screen = this->screens[i];
    if (screen.screen_name == screen_name) this->current_screen_i = i;
  }
}

void ScreenManager::setScreenDimensions(Vector dimensions) {
  this->screen_dimensions = dimensions;
}

Vector ScreenManager::ratioVec(Vector ratio) {
  return Vector(ratio.getX() * this->screen_dimensions.getX(), ratio.getY() * this->screen_dimensions.getY()); 
}

void ScreenManager::setWindowObject(sf::RenderWindow* window_ptr) {
  this->window_ptr = window_ptr;
}