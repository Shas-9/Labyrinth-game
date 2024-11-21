#ifndef SCREEN_INCLUDE
#define SCREEN_INCLUDE

#include "global.h"
#include "Button.h"
#include <vector>

using std::vector;
using std::pair;
using std::string;

struct ScreenButton {
  ScreenButton(Button* button, void (*func)()): button(button), func(func) {}
  Button* button;
  void (*func)();
};

struct ScreenImage {
  ScreenImage(string location, Vector image_dimensions, Vector scale): location(location), image_dimensions(image_dimensions), scale(scale) {}
  string location;
  Vector image_location;
  Vector image_dimensions;
  Vector scale;
};

struct ScreenText {
  ScreenText(string text, string text_location, int text_size, string font_location): text(text), text_location(text_location), text_size(text_size), font_location(font_location) {}
  string text;
  string text_location;
  int text_size;
  string font_location;
};

class Screen {
private:
  vector<ScreenButton> buttons;
  vector<ScreenText> texts;
  vector<ScreenImage> images;
public:
  string screen_name;

  Screen(string screen_name, vector<ScreenButton> buttons, vector<ScreenText> texts, vector<ScreenImage> images);
  void render();
  void update(sf::Event event);
};

#endif