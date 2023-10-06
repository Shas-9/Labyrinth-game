#ifndef UI_INCLUDE
#define UI_INCLUDE

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Vector.h"

class UI {
 private:
  int highscores_num;
  int* highscores_values;
  string* highscores_names;
  string current_state;
  Game game;
  Vector screen_dimensions;
  sf::RenderWindow* window_ptr;

 public:
  UI();
  UI(Vector screen_dimensions);
  UI(int width, int hight);
  void fetchHighScores();
  void startGames();
  void renderUI();
  void renderScreen();
};

#endif