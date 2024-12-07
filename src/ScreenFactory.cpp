#include "ScreenFactory.h"
#include "singleton/HighscoresManager.h"
#include "singleton/ScreenManager.h"
#include "Game.h"

#define TUTORIAL_BUTTON_COLOR sf::Color (74, 74, 46)
#define DEFAULT_BUTTON_COLOR sf::Color (22, 30, 43)
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
    sf::Color::White, DEFAULT_BUTTON_COLOR, sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 5);

  return Screen("main_screen", 
    vector<ScreenButton>({
      ScreenButton(play_button, SWITCH_SCREEN("highscores_screen")),
      ScreenButton(tutorial_btn, SWITCH_SCREEN("tutorial_screen"))
    }), 
    vector<ScreenText>({
      ScreenText("CatQuest", XVEC(Vector(0.25, 0.3)), 10, "fonts/cat_font.ttf", ScreenManager::getInstance().screen_dimensions.getX())
    }),
    vector<ScreenImage>({
      ScreenImage("images/UI.png", Vector(0, 0), Vector(1920, 1080), Vector(ScreenManager::getInstance().screen_dimensions.getY()/1080, ScreenManager::getInstance().screen_dimensions.getY()/1080))
    })
  );
}

Screen ScreenFactory::tutorialScreen() {
  Button* back_button = new Button("Back to Menu", XVEC(Vector(0.7, 0.72)), BUTTON_SIZE,
    sf::Color::White, DEFAULT_BUTTON_COLOR, sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 10);

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
      ScreenText(how_to_play, XVEC(Vector(0.1, 0.4)), 1.8, "fonts/arial.ttf", ScreenManager::getInstance().screen_dimensions.getX())
    }),
    vector<ScreenImage>({
      ScreenImage("images/UI.png", Vector(0, 0), Vector(1920, 1080), Vector(ScreenManager::getInstance().screen_dimensions.getY()/1080, ScreenManager::getInstance().screen_dimensions.getY()/1080))
    })
  );
}

Screen ScreenFactory::highscoresScreen() {
  Button* back_button = new Button("Back to Menu", XVEC(Vector(0.1, 0.72)), BUTTON_SIZE,
    sf::Color::White, DEFAULT_BUTTON_COLOR, sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 10);
  
  Button* start_button = new Button("Start Game", XVEC(Vector(0.7, 0.72)), BUTTON_SIZE,
    sf::Color::White, TUTORIAL_BUTTON_COLOR, sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 10);
  
  Button* name_button = new Button("", XVEC(Vector(0.645, 0.47)), BUTTON_SIZE,
    sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::White, BUTTON_TEXT_SIZE-10, 6);
  name_button->setCustomFont("fonts/MouldyCheese.ttf");

  std::string highscores = HighscoresManager::getInstance().formatHighscores();

  Screen scr("highscores_screen", 
    vector<ScreenButton>({
      ScreenButton(back_button, SWITCH_SCREEN("main_screen")),
      ScreenButton(start_button, []() {
        if (UTIL_CLASS.player_name.length() > 0) {
          ScreenManager::getInstance().switchScreen("game_screen"); // make this game screen?
          // initialize game object
          Game::getInstance().startGame();
        }
      }),
      ScreenButton(name_button, do_nothing),
    }), 
    vector<ScreenText>({
      ScreenText(highscores, XVEC(Vector(0.1, 0.4)), 2.4, "fonts/MouldyCheese.ttf", ScreenManager::getInstance().screen_dimensions.getX()),
      ScreenText("Enter your name:", XVEC(Vector(0.65, 0.4)), 2.4, "fonts/MouldyCheese.ttf", ScreenManager::getInstance().screen_dimensions.getX()),
      ScreenText("Press enter to play", XVEC(Vector(0.64, 0.58)), 2.4, "fonts/MouldyCheese.ttf", ScreenManager::getInstance().screen_dimensions.getX()),
    }),
    vector<ScreenImage>({
      ScreenImage("images/UI.png", Vector(0, 0), Vector(1920, 1080), Vector(ScreenManager::getInstance().screen_dimensions.getY()/1080, ScreenManager::getInstance().screen_dimensions.getY()/1080))
    })
  );

  scr.textEnteredHandler = [name_button](sf::Event event) {
    string allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ._";
    char c = static_cast<char>(event.text.unicode);
    if (allowed_chars.find(c) != string::npos && UTIL_CLASS.player_name.length() <= 20) {
      UTIL_CLASS.player_name += static_cast<char>(event.text.unicode);
      name_button->setString(UTIL_CLASS.player_name);
    } else if (event.text.unicode == 13 && UTIL_CLASS.player_name.length() > 0) {
      ScreenManager::getInstance().switchScreen("game_screen"); // make this game screen?
      // initialize game object
      Game::getInstance().startGame();
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

Screen ScreenFactory::gameScreen() {
  Button* pause_button = new Button("Pause Game", XVEC(Vector(0.75, 0.05)), BUTTON_SIZE, sf::Color::White, DEFAULT_BUTTON_COLOR, 
    sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 10);

  std::string hp_string = "HP: ";
  Button hp_text(hp_string, Vector(100, 50), Vector(100, 30), sf::Color::White, sf::Color::Transparent, 
    sf::Color::White, sf::Color::Transparent, 44, 5);
  hp_text.setCustomFont("fonts/MouldyCheese.ttf");

  std::string time_string = "Time: ";
  Button time_text(time_string, Vector(900, 50), Vector(100, 30), sf::Color::White, sf::Color::Transparent, 
    sf::Color::White, sf::Color::Transparent, 44, 5);
  time_text.setCustomFont("fonts/MouldyCheese.ttf");

  std::shared_ptr<string> test_str = std::make_shared<string>("for now");

  Screen game_screen("game_screen", 
    vector<ScreenButton>({
      ScreenButton(pause_button, []() {Game::getInstance().setGamePaused(true); ScreenManager::getInstance().switchScreen("pause_screen");})
      // ScreenButton(hp_text, SWITCH_SCREEN("pause_screen")),
      // ScreenButton(time_text, SWITCH_SCREEN("pause_screen")),
    }), 
    vector<ScreenText>({
      ScreenText(Game::getInstance().time_string, XVEC(Vector(0.04, 0.04)), 1.8, "fonts/arial.ttf", ScreenManager::getInstance().screen_dimensions.getX())
    }),
    vector<ScreenImage>({
      // ScreenImage("images/UI.png", Vector(0, 0), Vector(1920, 1080), Vector(ScreenManager::getInstance().screen_dimensions.getY()/1080, ScreenManager::getInstance().screen_dimensions.getY()/1080))
    })
  );

  game_screen.keyPressedHandler = [](sf::Event event) {
    if (event.key.code == sf::Keyboard::A) Game::getInstance().player.setMovementDirection(0, true);
    if (event.key.code == sf::Keyboard::D) Game::getInstance().player.setMovementDirection(1, true);
    if (event.key.code == sf::Keyboard::W) Game::getInstance().player.setMovementDirection(2, true);
    if (event.key.code == sf::Keyboard::S) Game::getInstance().player.setMovementDirection(3, true);
  };

  game_screen.keyReleasedHandler = [](sf::Event event) {
    if (event.key.code == sf::Keyboard::A) Game::getInstance().player.setMovementDirection(0, false);
    if (event.key.code == sf::Keyboard::D) Game::getInstance().player.setMovementDirection(1, false);
    if (event.key.code == sf::Keyboard::W) Game::getInstance().player.setMovementDirection(2, false);
    if (event.key.code == sf::Keyboard::S) Game::getInstance().player.setMovementDirection(3, false);

    if (event.key.code == sf::Keyboard::Escape) {
      Game::getInstance().setGamePaused(true);
      ScreenManager::getInstance().switchScreen("pause_screen");
      // time_elapsed = clock->getElapsedTime().asSeconds();
      // bool resume_button_pressed = false;

      // while (!(resume_button_pressed)) {
      //   resume_button_pressed = this->pause();
      // }
      // clock->restart();
    }
  };

  return game_screen;
}

Screen ScreenFactory::pauseScreen() {
  Button* quit_game_button = new Button("Quit game", XVEC(Vector(0.1, 0.72)), BUTTON_SIZE,
    sf::Color::White, DEFAULT_BUTTON_COLOR, sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 10);

  Button* resume_button = new Button("Resume game", XVEC(Vector(0.7, 0.72)), BUTTON_SIZE,
    sf::Color::White, TUTORIAL_BUTTON_COLOR, sf::Color::White, MOUSE_OVER_COLOR, BUTTON_TEXT_SIZE, 10);

  return Screen("pause_screen", 
    vector<ScreenButton>({
      ScreenButton(resume_button, []() {Game::getInstance().setGamePaused(false); ScreenManager::getInstance().switchScreen("game_screen");}),
      ScreenButton(quit_game_button, []() {Game::getInstance().setGamePaused(false); ScreenManager::getInstance().switchScreen("main_screen");}),
    }), 
    vector<ScreenText>({
      ScreenText("Game Paused", XVEC(Vector(0.26, 0.3)), 6.8, "fonts/cat_font.ttf", ScreenManager::getInstance().screen_dimensions.getX()),
      ScreenText("All progress will be lost if you quit.", XVEC(Vector(0.32, 0.6)), 2.4, "fonts/MouldyCheese.ttf", ScreenManager::getInstance().screen_dimensions.getX()),
    }),
    vector<ScreenImage>({
      ScreenImage("images/UI.png", Vector(0, 0), Vector(1920, 1080), Vector(ScreenManager::getInstance().screen_dimensions.getY()/1080, ScreenManager::getInstance().screen_dimensions.getY()/1080))
    })
  );
}