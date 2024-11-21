#include "ScreenManager.h"

ScreenManager& ScreenManager::getInstance() {
  static ScreenManager instance;
  return instance;
}

ScreenManager::ScreenManager() {}

void ScreenManager::switchScreen(std::string screen_name) {
  for (int i = 0; i < this->screens.size(); i++) {
    Screen &screen = this->screens[i];
    if (screen.screen_name == screen_name) this->current_screen_i = i;
  }
}