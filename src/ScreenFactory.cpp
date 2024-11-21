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
  
  Button* name_button = new Button("", XVEC(Vector(0.645, 0.47)), BUTTON_SIZE,
    sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::White, BUTTON_TEXT_SIZE-10, 6);

  std::string highscores = HighscoresManager::getInstance().formatHighscores();

  Screen scr("highscores_screen", 
    vector<ScreenButton>({
      ScreenButton(back_button, SWITCH_SCREEN("main_screen")),
      ScreenButton(name_button, do_nothing),
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

  scr.textEnteredHandler = [name_button](sf::Event event) {
    string allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ._";
    char c = static_cast<char>(event.text.unicode);
    if (allowed_chars.find(c) != string::npos && UTIL_CLASS.player_name.length() <= 20) {
      UTIL_CLASS.player_name += static_cast<char>(event.text.unicode);
      name_button->setString(UTIL_CLASS.player_name);
    } else if (event.text.unicode == 13 && UTIL_CLASS.player_name.length() > 0) {
      ScreenManager::getInstance().switchScreen("main_screen");
      // // Start timer here
      // this->startGame();
      // // End timer
      // // Calculate score
      // this->showScoreScreen()
      // return true;
    }
  };

  scr.keyPressedHandler = [name_button](sf::Event event) {
    if (event.key.code == sf::Keyboard::BackSpace && UTIL_CLASS.player_name.length() > 0) {
      UTIL_CLASS.player_name.pop_back();
      name_button->setString(UTIL_CLASS.player_name);
    }
  };

  return scr;
}