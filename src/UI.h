#ifndef UI_INCLDUE
#define UI_INCLUDE

#include "Game.h"

class UI {
 private:
  int highscores_num;
  int* highscores_values;
  string* highscores_names;
  string current_state;
  Game game;

 public:
  UI();
  void fetchHighScores();
  void startGames();
  void renderUI();
  void renderScreen();
};

#endif