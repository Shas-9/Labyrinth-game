#ifndef SCREEN_FACTORY_INCLUDE
#define SCREEN_FACTORY_INCLUDE

#include "global.h"
#include "Screen.h"

class ScreenFactory {
public:
  static Screen mainScreen();
  static Screen tutorialScreen();
  static Screen highscoresScreen();
  static Screen gameScreen();
  static Screen pauseScreen();
};

#endif