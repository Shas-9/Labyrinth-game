#ifndef SCREEN_MANAGER_INCLUDE
#define SCREEN_MANAGER_INCLUDE

#include "global.h"
#include "Button.h"
#include <vector>

using std::vector;
using std::pair;
using std::string;

class ScreenManager {
private:
  ScreenManager();
public:
  static ScreenManager& getInstance();
  ScreenManager(ScreenManager const&) = delete;
  void operator=(ScreenManager const&) = delete;

  int current_screen_i;
  std::vector<Screen> screens;
  void switchScreen(std::string name);
};

#endif