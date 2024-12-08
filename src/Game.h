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

#include <memory>

class Game : public Singleton<Game> {
private:
  friend class Singleton<Game>;
  Game();

  std::shared_ptr<Environment> environment;
  bool is_game_paused;
  bool is_game_won;
  bool is_game_over;
  sf::Sprite* ground_sprite;
  sf::Clock clock;
  long int time_offset;

public:
  std::shared_ptr<string> time_string;
  std::shared_ptr<string> health_string;
  Player player;
  void startGame();
  void winGame();
  void loseGame();
  void setGamePaused(bool isPaused);

  void update();
  void render();
};

#endif