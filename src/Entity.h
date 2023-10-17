#ifndef ENTITY_INCLUDE
#define ENTITY_INCLUDE

#include <iostream>
using std::cout;
using std::endl;

#include "RenderedObject.h"
#include "Obstacle.h"
#include "Utility.h"

class Entity : public RenderedObject {
protected:
       // Movement
       bool moving_left;
       bool moving_right;
       bool moving_up;
       bool moving_down;
       int movement_speed;

       Obstacle* obstacles;
       int obstacles_num;

       // Animation
       sf::Sprite* sprite;
       vector<vector<sf::IntRect*>> walking_frames;
       int current_frames_index;
       int current_animation_frame;

       // Properties
       int health;
       int max_health;
       int attack_damage;

public:
       Entity();
       Entity(
              Vector position,
              Vector dimensions,
              string type,
              int movement_speed,
              int health,
              int attack_damage,
              Obstacle* obstacles,
              int obstacles_num
       );

       // Health
       int getHealth();
       void loseHealth(int lost_health);
       void gainHealth(int extra_health);

       virtual void update() = 0;

       // Movement
       void moveUp();
       void moveDown();
       void moveRight();
       void moveLeft();

       void setMovementDirection(int direction, bool is_moving);
       int getMovementDirection(int direction);

       bool canMove();

       void render(sf::RenderWindow *window, Vector camera_position);
};

#endif