#ifndef UI_INCLUDE
#define UI_INCLUDE

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>

#include "Game.h"
#include "Vector.h"
#include "Button.h"
#include "Utility.h"

// TODO: 
/*

1. PUT ALL TEXTURES IN AN UNORDEREDMAP SO THAT WE DONT LOAD THE SAME TEXTURE MULTIPLE TIMES
2. ADD DIFFERENT FUNCTIONS FOR ALL SCREENS TO LOAD EVERYHTING REQUIRED FOR THE SCREEN

*/

class UI {
 private:
  int score;
  std::string player_name;
  std::map<int, std::string> highscores;
  int num_highscores;
  std::string current_state;
  Game game;
  Vector screen_dimensions;
  sf::RenderWindow* window_ptr;
  sf::Event* event_ptr;
  sf::Clock* clock;
  std::unordered_map<std::string, sf::Texture> textures_map;
  std::unordered_map<std::string, sf::Sprite> sprites_map;
  std::unordered_map<std::string, sf::Font> fonts_map;


  void renderUI();
  bool drawTutorial();
  bool enterName();

 public:
  UI();
  UI(Vector screen_dimensions);
  UI(int width, int hight);
  void fetchHighScores();
  void startGame();
  void drawGame();
  
  void pushHighScore();
  bool gameOverScreen();
  bool gameWinScreen();
  
};

#endif