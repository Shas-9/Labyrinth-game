#include "Screen.h"
#define TUTORIAL_BUTTON_COLOR sf::Color (74, 74, 46)
#define PLAY_BUTTON_COLOR sf::Color (22, 30, 43)
#define MOUSE_OVER_COLOR sf::Color (59, 5, 44)

// TODO:
// needs to be responsive.. cant use macros for this
// maybe move to the utils class?
#define BUTTON_TEXT_SIZE int (30)
#define BUTTON_SIZE XVEC(Vector(0.2, 0.1))


Screen::Screen(string screen_name, vector<ScreenButton> buttons, vector<ScreenText> texts, vector<ScreenImage> images): screen_name(screen_name), buttons(buttons), texts(texts), images(images) {}

void Screen::render() {
  // render all the buttons
  for (ScreenButton& button : this->buttons) {
    button.button->drawButton(*UTIL_CLASS.window_ptr);
  }

  // render the images

  // render the text
}

void Screen::update(sf::Event event) {
  switch (event.type) {
    case sf::Event::Closed:
      (*UTIL_CLASS.window_ptr).close();
      break;

    case sf::Event::MouseButtonPressed:
      for (ScreenButton& button : this->buttons) {
        if ((button.button->isMouseOver(*UTIL_CLASS.window_ptr))) {
          button.func();
        }
      }
      break;

    case sf::Event::MouseMoved:
      for (ScreenButton& button : this->buttons) {
        if (button.button->isMouseOver(*UTIL_CLASS.window_ptr)) {
          button.button->setBackToColor(MOUSE_OVER_COLOR);
        } else {
          button.button->setBackToColor(PLAY_BUTTON_COLOR);
        }
      }
      break;
  }
}