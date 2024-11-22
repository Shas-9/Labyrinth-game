#ifndef SCREEN_MANAGER_INCLUDE
#define SCREEN_MANAGER_INCLUDE

#define XVEC ScreenManager::getInstance().ratioVec

#include "../global.h"
#include "../Screen.h"
#include "Singleton.h"

#include <vector>

using std::vector;
using std::pair;
using std::string;

class ScreenManager : public Singleton<ScreenManager> {
private:
  ScreenManager();
  friend class Singleton<ScreenManager>;
public:
  // Window pointer
  sf::RenderWindow* window_ptr;
  void setWindowObject(sf::RenderWindow* window_ptr);

  // Screen dimensions
  Vector screen_dimensions;
  void setScreenDimensions(Vector dimensions);
  Vector ratioVec(Vector ratio);

  // Screens
  int current_screen_i;
  std::vector<Screen> screens;
  void switchScreen(std::string name);
};

#endif