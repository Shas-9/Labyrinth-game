#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Environment.h"
#include "Utility.h"
#include "Button.h"

class Game {
 private:
  Environment *environment;
  Player player;
  bool isGamePaused;
  bool isGameOver;
  sf::Event* event_ptr;
  sf::RenderWindow *window_ptr;

 public:
  Game();
  Game(sf::RenderWindow *window, sf::Event* event_ptr);
  void updateAll();
  void renderAll();
  void pause();
  void endGame();
};

#endif