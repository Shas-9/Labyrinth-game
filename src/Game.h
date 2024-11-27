#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "singleton/Singleton.h"
#include "Player.h"
#include "Environment.h"
#include "singleton/Utility.h"
#include "Button.h"
#include "IronSpider.h"

class Game : public Singleton<Game> {
private:
  friend class Singleton<Game>;
  Game();

  Environment *environment;
  bool is_game_paused;
  bool is_game_won;
  bool is_game_over;
  sf::Clock* clock;
  sf::Sprite* ground_sprite;

public:
  Player player;
  void startGame();
  void setGamePaused(bool isPaused);
  bool isGameWon();
  int getScore();

  void update(sf::Event event);
  void render();
};

#endif