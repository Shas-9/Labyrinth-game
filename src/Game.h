#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include <SFML/Graphics.hpp>

#include "Player.h"

class Game {
 private:
  Environment *environment;
  Player player;
  bool isGamePaused;
  sf::RenderWindow *window_ptr;

 public:
  Game();
  Game(sf::RenderWindow *window);
  void updateAll();
  void renderAll();
  void pause();
};

#endif