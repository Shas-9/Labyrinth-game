#ifndef UI_INCLUDE
#define UI_INCLUDE

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>

#include "Game.h"
#include "Vector.h"
#include "Button.h"
#include "Screen.h"

class UI {
public:
  UI();
  UI(Vector screen_dimensions);
  UI(int width, int hight);
};

#endif