#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

#include <SFML/Graphics.hpp>

#include "Utility.h"
#include "Entity.h"
#include "Environment.h"
#include "Enemy.h"

class Player : public Entity {
protected:
  int score;
  Environment* environment;

public:
  Player();
  Player(
    Vector position,
    Vector dimensions,
    string type,
    int movement_speed,
    int health,
    int attack_damage,
    Environment* environment
  );
  int getScore();

  void render(sf::RenderWindow *window, Vector screen_dimensions);
  void update() override;
};

#endif