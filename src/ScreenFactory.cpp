#include "ScreenFactory.h"

#define TUTORIAL_BUTTON_COLOR sf::Color (74, 74, 46)
#define PLAY_BUTTON_COLOR sf::Color (22, 30, 43)
#define MOUSE_OVER_COLOR sf::Color (59, 5, 44)

// TODO:
// needs to be responsive.. cant use macros for this
// maybe move to the utils class?
#define BUTTON_TEXT_SIZE int (30)
#define BUTTON_SIZE XVEC(Vector(0.2, 0.1))

// #define SWITCH_SCREEN( []() {ScreenManager::getInstance().switchScreen("");}
#define SWITCH_SCREEN(screen_name) []() { ScreenManager::getInstance().switchScreen(screen_name); }

Screen ScreenFactory::mainScreen() {
  Button* tutorial_btn = new Button("How to play", XVEC(Vector(0.1, 0.72)), BUTTON_SIZE,
    TUTORIAL_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 5);
  
  Button* play_button = new Button("Play Game", XVEC(Vector(0.7, 0.72)), BUTTON_SIZE,
    PLAY_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 5);

  return Screen("main_screen", 
    vector<ScreenButton>({
      ScreenButton(play_button, SWITCH_SCREEN("play_screen")),
      ScreenButton(tutorial_btn, SWITCH_SCREEN("test_screen"))
    }), 
    vector<ScreenText>({
      ScreenText("CatQuest", XVEC(Vector(0.25, 0.3)), 10, "fonts/cat_font.ttf", UTIL_CLASS.screen_dimensions.getX())
    }),
    vector<ScreenImage>({
      ScreenImage("images/UI.png", Vector(0, 0), Vector(1920, 1080), Vector(UTIL_CLASS.screen_dimensions.getY()/1080, UTIL_CLASS.screen_dimensions.getY()/1080))
    })
  );
}

Screen ScreenFactory::testScreen() {  
  Button* play_button = new Button("Lol button", XVEC(Vector(0.4, 0.6)), BUTTON_SIZE,
    PLAY_BUTTON_COLOR, sf::Color::White, BUTTON_TEXT_SIZE, 5);
  
  return Screen("test_screen", vector<ScreenButton>({ScreenButton(play_button, SWITCH_SCREEN("main_screen"))}), vector<ScreenText>(), vector<ScreenImage>());
}
