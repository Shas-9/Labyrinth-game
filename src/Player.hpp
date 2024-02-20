#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

#include <SFML/Graphics.hpp>

#include "Utility.hpp"
#include "Entity.hpp"
#include "Environment.hpp"
#include "Enemy.hpp"

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