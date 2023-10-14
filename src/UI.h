#ifndef UI_INCLUDE
#define UI_INCLUDE

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <map>
#include <string>

// #include "Game.h"
#include "Vector.h"
#include "Button.h"


class UI {
 private:
  int score;
  std::string player_name;
  std::map<std::string, int> highscores;
  std::string current_state;
  // Game game;
  Vector screen_dimensions;
  sf::RenderWindow* window_ptr;
  sf::Event* event_ptr;

  void renderUI();
  bool drawTutorial();

 public:
  UI();
  UI(Vector screen_dimensions);
  UI(int width, int hight);
  void fetchHighScores();
  void startGames();
  void renderScreen();
  void enterName();
};

#endif