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
       bool moving_left;
       bool moving_right;
       bool moving_up;
       bool moving_down;
       sf::Sprite* sprite;
       vector<vector<sf::IntRect*>> walking_frames;
       int current_frames_index;
       int current_animation_frame;
       // Weapon* current_item;
       Environment* environment;

public:
       Player();
       Player(
              Vector position,
              Vector dimensions,
              string type,
              string movement_animation,
              int movement_speed,
              int health,
              int attack_damage,
              string attack_animation,
              string death_animation,
              Environment* environment,
              sf::Texture* player_texture
       );
       void moveUp();
       void moveDown();
       void moveRight();
       void moveLeft();
       void attack();  // If Player has Weapon, use it instead
       void pickUpItem();
       void dropItem();
       int getScore();
       void setMovementDirection(int direction, bool is_moving);
       int getMovementDirection(int direction);
       bool canMove();
       void frames_handler();
       // Item* getNearbyItem();

       void getNearbyItem();

       void render(sf::RenderWindow *window);
       void update() override;
};

#endif