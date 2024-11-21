#include "ScreenFactory.h"
#include "HighscoresManager.h"

#define TUTORIAL_BUTTON_COLOR sf::Color (74, 74, 46)
#define DEFAULT_BUTTON_COLOT sf::Color (22, 30, 43)
#define MOUSE_OVER_COLOR sf::Color (59, 5, 44)

// TODO:
// needs to be responsive.. cant use macros for this
// maybe move to the utils class?
#define BUTTON_TEXT_SIZE int (30)
#define BUTTON_SIZE XVEC(Vector(0.2, 0.1))

#define SWITCH_SCREEN(screen_name) []() { ScreenManager::getInstance().switchScreen(screen_name); }

void do_nothing() {}

Screen ScreenFactory::mainScreen() {
  Button* tutorial_btn = new Button("How to play", XVEC(Vector(0.1, 0.72)), BUTTON_SIZE,
    sf::Color::White, TUTORIAL_BUTTON_COLOR, sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 5);
  
  Button* play_button = new Button("Play Game", XVEC(Vector(0.7, 0.72)), BUTTON_SIZE,
    sf::Color::White, DEFAULT_BUTTON_COLOT, sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 5);

  return Screen("main_screen", 
    vector<ScreenButton>({
      ScreenButton(play_button, SWITCH_SCREEN("highscores_screen")),
      ScreenButton(tutorial_btn, SWITCH_SCREEN("tutorial_screen"))
    }), 
    vector<ScreenText>({
      ScreenText("CatQuest", XVEC(Vector(0.25, 0.3)), 10, "fonts/cat_font.ttf", UTIL_CLASS.screen_dimensions.getX())
    }),
    vector<ScreenImage>({
      ScreenImage("images/UI.png", Vector(0, 0), Vector(1920, 1080), Vector(UTIL_CLASS.screen_dimensions.getY()/1080, UTIL_CLASS.screen_dimensions.getY()/1080))
    })
  );
}

Screen ScreenFactory::tutorialScreen() {
  Button* back_button = new Button("Back to Menu", XVEC(Vector(0.7, 0.72)), BUTTON_SIZE,
    sf::Color::White, DEFAULT_BUTTON_COLOT, sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 10);

  std::string how_to_play;
  how_to_play = ("Gameplay Instructions:\n\n"
    "Use the 'W' 'A' 'S' 'D' keys to move around the screen. "
    "Find the cat within the maze to win.\n"
    "Avoid the spiders, they will decrease your health points. "
    "If your health reaches 0, you lose.\n\n"
    "Press the menu button to return to the menu.");

  return Screen("tutorial_screen", 
    vector<ScreenButton>({
      ScreenButton(back_button, SWITCH_SCREEN("main_screen")),
    }), 
    vector<ScreenText>({
      ScreenText(how_to_play, XVEC(Vector(0.1, 0.4)), 1.8, "fonts/arial.ttf", UTIL_CLASS.screen_dimensions.getX())
    }),
    vector<ScreenImage>({
      ScreenImage("images/UI.png", Vector(0, 0), Vector(1920, 1080), Vector(UTIL_CLASS.screen_dimensions.getY()/1080, UTIL_CLASS.screen_dimensions.getY()/1080))
    })
  );
}

Screen ScreenFactory::highscoresScreen() {
  Button* back_button = new Button("Back to Menu", XVEC(Vector(0.7, 0.72)), BUTTON_SIZE,
    sf::Color::White, DEFAULT_BUTTON_COLOT, sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 10);
  
  Button* name = new Button("", XVEC(Vector(0.645, 0.47)), BUTTON_SIZE,
    sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::White, BUTTON_TEXT_SIZE, 10);

  std::string highscores = HighscoresManager::getInstance().formatHighscores();

  return Screen("highscores_screen", 
    vector<ScreenButton>({
      ScreenButton(back_button, SWITCH_SCREEN("main_screen")),
      ScreenButton(name, do_nothing),
    }), 
    vector<ScreenText>({
      ScreenText(highscores, XVEC(Vector(0.1, 0.4)), 3, "fonts/MouldyCheese.ttf", UTIL_CLASS.screen_dimensions.getX()),
      ScreenText("Enter your name:", XVEC(Vector(0.65, 0.4)), 2.4, "fonts/MouldyCheese.ttf", UTIL_CLASS.screen_dimensions.getX()),
      ScreenText("Press enter to play", XVEC(Vector(0.64, 0.58)), 2.4, "fonts/MouldyCheese.ttf", UTIL_CLASS.screen_dimensions.getX()),
    }),
    vector<ScreenImage>({
      ScreenImage("images/UI.png", Vector(0, 0), Vector(1920, 1080), Vector(UTIL_CLASS.screen_dimensions.getY()/1080, UTIL_CLASS.screen_dimensions.getY()/1080))
    })
  );
}

Screen ScreenFactory::testScreen() {  
  Button* play_button = new Button("Lol button", XVEC(Vector(0.4, 0.6)), BUTTON_SIZE,
    sf::Color::White, DEFAULT_BUTTON_COLOT, sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 5);
  
  return Screen("test_screen", vector<ScreenButton>({ScreenButton(play_button, SWITCH_SCREEN("main_screen"))}), vector<ScreenText>(), vector<ScreenImage>());
}
