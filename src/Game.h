#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Player.h"
#include "Environment.h"
#include "Utility.h"
#include "Button.h"
#include "IronSpider.h"

class Game {
 private:
  Environment *environment;
  Player player;
  bool is_game_paused;
  bool is_game_won;
  bool is_game_over;
  sf::Event* event_ptr;
  sf::RenderWindow *window_ptr;
  bool is_game_won;

 public:
  Game();
  Game(sf::RenderWindow *window, sf::Event* event_ptr, Vector screen_dimensions, sf::Clock* clock);
  
  bool pause();
  bool confirmationScreen();
  bool isGameWon();
};

#endif