#ifndef UI_INCLUDE
#define UI_INCLUDE

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>

#include "Game.h"
#include "Vector.h"
#include "Button.h"
#include "Screen.h"

class UI {
 private:
  int score;
  std::string player_name;
  std::map<int, std::string> highscores;
  int num_highscores;
  std::string current_state;
  sf::Clock* clock;

  void renderUI();
  bool drawTutorial();
  bool enterName();

 public:
  UI();
  UI(Vector screen_dimensions);
  UI(int width, int hight);
  void startGame();
  void drawGame();
  
  void pushHighScore();
  bool gameOverScreen();
  bool gameWinScreen();
};

#endif