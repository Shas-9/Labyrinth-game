#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Player.h"
#include "Environment.h"
#include "singleton/Utility.h"
#include "Button.h"
#include "IronSpider.h"

class Game {
 private:
  Environment *environment;
  Player player;
  bool is_game_paused;
  bool is_game_won;
  bool is_game_over;
  sf::Clock* clock;

 public:
  Game();
  Game(sf::Clock* clock);
  
  bool pause();
  bool confirmationScreen();
  bool isGameWon();
  int getScore();
};

#endif