#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

#include <SFML/Graphics.hpp>

#include "singleton/Utility.h"
#include "Entity.h"
#include "Environment.h"
#include "Enemy.h"

#include <memory>

class Player : public Entity {
protected:
  int score;
  std::shared_ptr<Environment> environment;

public:
  Player();
  Player(
    Vector position,
    Vector dimensions,
    string type,
    int movement_speed,
    int health,
    int attack_damage,
    std::shared_ptr<Environment> environment
  );
  int getScore();

  void render(sf::RenderWindow *window, Vector screen_dimensions);
  void update();
};

#endif