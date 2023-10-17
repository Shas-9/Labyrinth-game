#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

#include <SFML/Graphics.hpp>

#include "Utility.h"
#include "Entity.h"
#include "Environment.h"
#include "Enemy.h"
// #include "Weapon.h"

class Player : public Entity {
protected:
       int score;
       // Weapon* current_item;
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
              Environment* environment,
              sf::Texture* player_texture
       );
       void attack();  // If Player has Weapon, use it instead
       void pickUpItem();
       void dropItem();
       int getScore();
       // Item* getNearbyItem();

       void getNearbyItem();

       void render(sf::RenderWindow *window, Vector screen_dimensions);
       void update() override;
};

#endif