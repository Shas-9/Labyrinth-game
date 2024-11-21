#include "ScreenManager.h"

ScreenManager& ScreenManager::getInstance() {
  static ScreenManager instance;
  return instance;
}

ScreenManager::ScreenManager() {}

void ScreenManager::switchScreen(std::string screen_name) {
  std::cout << "attempting to change screens" << std::endl;
  for (int i = 0; i < this->screens.size(); i++) {
    Screen &screen = this->screens[i];
    std::cout << "looping over screen of name " << screen.screen_name << ", but looking for " << screen_name << std::endl;
    if (screen.screen_name == screen_name) {
      std::cout << "Changing screens, found index " << i << std::endl;
      this->current_screen_i = i;
    }
  }
}