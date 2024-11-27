#include "Screen.h"
#include "singleton/ScreenManager.h"

#define TUTORIAL_BUTTON_COLOR sf::Color (74, 74, 46)
#define PLAY_BUTTON_COLOR sf::Color (22, 30, 43)
#define MOUSE_OVER_COLOR sf::Color (59, 5, 44)

// TODO:
// needs to be responsive.. cant use macros for this
// maybe move to the utils class?
#define BUTTON_TEXT_SIZE int (30)
#define BUTTON_SIZE XVEC(Vector(0.2, 0.1))

Screen::Screen(string screen_name, vector<ScreenButton> buttons, vector<ScreenText> texts, vector<ScreenImage> images): screen_name(screen_name), buttons(buttons), texts(texts), images(images) {
  // by default set keypressed handlers to do nothing
  this->keyPressedHandler = [](sf::Event event) {};
  this->keyReleasedHandler = [](sf::Event event) {};
  this->textEnteredHandler = [](sf::Event event) {};
}

void Screen::render() {
  // render the images
  for (ScreenImage& image : this->images) {
    (*ScreenManager::getInstance().window_ptr).draw(*image.sprite);
  }

  // render the text
  for (ScreenText& text : this->texts) {
    (*ScreenManager::getInstance().window_ptr).draw(*text.text);
  }

  // render all the buttons
  for (ScreenButton& button : this->buttons) {
    button.button->drawButton(*ScreenManager::getInstance().window_ptr);
  }
}

void Screen::update(sf::Event event) {
  switch (event.type) {
    case sf::Event::Closed:
      (*ScreenManager::getInstance().window_ptr).close();
      break;

    case sf::Event::MouseButtonPressed:
      for (ScreenButton& button : this->buttons) {
        if ((button.button->isMouseOver(*ScreenManager::getInstance().window_ptr))) {
          button.button->setDefaultColor();
          button.func();
        }
      }
      break;

    case sf::Event::MouseMoved:
      for (ScreenButton& button : this->buttons) {
        if (button.button->isMouseOver(*ScreenManager::getInstance().window_ptr)) {
          button.button->setHoverColor();
        } else {
          button.button->setDefaultColor();
        }
      }
      break;

    case sf::Event::KeyPressed:
      this->keyPressedHandler(event);
      break;

    case sf::Event::KeyReleased:
      this->keyReleasedHandler(event);
      break;

    case sf::Event::TextEntered:
      this->textEnteredHandler(event);
      break;
  }
}